// todo: remove macros, they're not useful here, debugging and maintainance bad
// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset


void add_voxel_face_colors(
    color_rgb_array_d* color_rgbs,
    color_rgb voxel_color,
    const byte direction
) {
    for (byte a = 0; a < voxel_face_vertices_length; a++) {
        color_rgb vertex_color = voxel_color;

        if (direction == direction_down) {
            color_rgb_multiply_float(&vertex_color, 0.33f);
        } else if (direction == direction_front) {
            color_rgb_multiply_float(&vertex_color, 0.44f);
        } else if (direction == direction_left) {
            color_rgb_multiply_float(&vertex_color, 0.55f);
        } else if (direction == direction_back) {
            color_rgb_multiply_float(&vertex_color, 0.66f);
        } else if (direction == direction_right) {
            color_rgb_multiply_float(&vertex_color, 0.76f);
        }
        add_to_color_rgb_array_d(color_rgbs, vertex_color);
    }
}

void add_voxel_face(
    int_array_d *indicies,
    float3_array_d* vertices,
    const float3 offset,
    const float voxel_scale,
    const int* indiciesf,
    const float3* verticesf
) {
    expand_capacity_int_array_d(indicies, voxel_face_indicies_length);
    for (int i = 0, j = indicies->size; i < voxel_face_indicies_length; i++, j++) {
        indicies->data[j] = vertices->size + indiciesf[i];
    }
    indicies->size += voxel_face_indicies_length;

    expand_capacity_float3_array_d(vertices, voxel_face_vertices_length);
    for (int i = 0, j = vertices->size; i < voxel_face_vertices_length; i++, j++) {
        vertices->data[j] = verticesf[i];
        float3_scale_p(&vertices->data[j], voxel_scale);
        float3_add_float3_p(&vertices->data[j], offset);
    }
    vertices->size += voxel_face_vertices_length;
}

void build_voxel_faces_c(
    const VoxelNode* root,
    const VoxelNode** cneighbors,
    const byte* cneighbor_lods,
    int_array_d* indicies,
    float3_array_d* vertices,
    color_rgb_array_d* color_rgbs,
    const color_rgb voxel_color,
    const float scale,
    const float3 offset,
    byte depth,
    int3 position
) {
    const byte edge = 0; // 255
    byte neighbors[6];
    for (int i = 0; i < 6; i++) {
        neighbors[i] = is_adjacent_all_solid(
            NULL,
            edge,
            cneighbors,
            cneighbor_lods,
            root,
            position,
            i,          // direction
            depth
        );
    }

    for (int i = 0; i < 6; i++) {
        if (!neighbors[i] || neighbors[i] == 255) {
            const int* indiciesf = voxel_face_indicies_n + i * voxel_face_indicies_length;
            const float3* verticesf = voxel_face_vertices_n[i];

            add_voxel_face(
                indicies,
                vertices,
                offset,
                scale,
                indiciesf,
                verticesf
            );

#ifdef DISABLE_AO
            add_voxel_face_colors(
                color_rgbs,
                voxel_color,
                i
            );
#else
            add_voxel_face_colors_ao(
                color_rgbs,
                voxel_color,
                i,
                neighbors
            );
#endif
        }
        /*if (i != 1 && i != 3) { // why does up need different indicies??
            is_positive = !is_positive;
        }*/
    }
}

void build_octree_chunk_colors_d(
    const VoxelNode* root,
    const VoxelNode* parent_node,
    const VoxelNode* node,
    const VoxelNode** neighbors,
    const byte* neighbor_lods,
    const ColorRGBs *colorRGBs,
    int_array_d *indicies,
    float3_array_d* vertices,
    color_rgb_array_d* color_rgbs,
    const byte max_depth,
    byte depth,
    int3 position,
    const byte node_index,
    const float3 total_mesh_offset,
    const float vox_scale
) {
    if (node == NULL) {
        return;
    }
    if (depth >= max_depth || is_closed_VoxelNode(node)) {
        const byte voxel = node->value;
        if (voxel) {
            const byte voxel_index = voxel - 1;
            if (voxel_index >= colorRGBs->length) {
                zox_logw("voxel_index oob: %i / %i", voxel_index, colorRGBs->length);
                return;
            }
            const color_rgb voxel_color = colorRGBs->value[voxel_index];
            const float voxel_scale = real_chunk_scale * octree_scales3[depth] * vox_scale;
            float3 offset = float3_from_int3(position);
            float3_scale_p(&offset, voxel_scale);
            float3_add_float3_p(&offset, total_mesh_offset);

            build_voxel_faces_c(
                root,
                neighbors,
                neighbor_lods,
                indicies,
                vertices,
                color_rgbs,
                voxel_color,
                voxel_scale,
                offset,
                depth,
                position
            );
        }
    } else {
        depth++;
        int3_multiply_int_p(&position, 2);
        VoxelNode* kids = get_children_VoxelNode(node);
        for (byte i = 0; i < octree_length; i++) {
            int3 child_position = int3_add(position, octree_positions[i]);
            build_octree_chunk_colors_d(
                root,
                node,
                &kids[i],
                neighbors,
                neighbor_lods,
                colorRGBs,
                indicies,
                vertices,
                color_rgbs,
                max_depth,
                depth,
                child_position,
                i,
                total_mesh_offset,
                vox_scale);
        }
    }
}

void build_node_mesh_colors(
    const VoxelNode *node,
    const ColorRGBs *colorRGBs,
    MeshIndicies *meshIndicies,
    MeshVertices *meshVertices,
    MeshColorRGBs *meshColorRGBs,
    const byte chunk_depth,
    const VoxelNode *neighbors[],
    const byte neighbor_lods[],
    const float3 total_mesh_offset,
    const float vox_scale) {
    int_array_d* indicies = create_int_array_d(initial_dynamic_array_size);
    float3_array_d* vertices = create_float3_array_d(initial_dynamic_array_size);
    color_rgb_array_d* color_rgbs = create_color_rgb_array_d(initial_dynamic_array_size);
    build_octree_chunk_colors_d(
        node,
        NULL,
        node,
        neighbors,
        neighbor_lods,
        colorRGBs,
        indicies,
        vertices,
        color_rgbs,
        chunk_depth,
        0,
        int3_zero,
        0,
        total_mesh_offset,
        vox_scale);
    clear_mesh(
        meshIndicies,
        meshVertices,
        meshColorRGBs);
    meshIndicies->length = indicies->size;
    meshVertices->length = vertices->size;
    meshColorRGBs->length = color_rgbs->size;
    meshIndicies->value = zinalize_int_array_d(indicies);
    meshVertices->value = zinalize_float3_array_d(vertices);
    meshColorRGBs->value = zinalize_color_rgb_array_d(color_rgbs);
}


// builds the character vox meshes
void ChunkColorsBuildSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ChunkMeshDirty)
    zox_sys_in(VoxelNode)
    zox_sys_in(NodeDepth)
    zox_sys_in(RenderLod)
    zox_sys_in(ChunkNeighbors)
    zox_sys_in(ColorRGBs)
    zox_sys_in(ChunkSize)
    zox_sys_in(VoxScale)
    zox_sys_out(MeshIndicies)
    zox_sys_out(MeshVertices)
    zox_sys_out(MeshColorRGBs)
    zox_sys_out(MeshDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ChunkMeshDirty, chunkMeshDirty)
        zox_sys_i(VoxelNode, voxelNode)
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(ChunkNeighbors, chunkNeighbors)
        zox_sys_i(ColorRGBs, colorRGBs)
        zox_sys_i(ChunkSize, chunkSize)
        zox_sys_i(VoxScale, voxScale)
        zox_sys_o(MeshDirty, meshDirty)
        zox_sys_o(MeshIndicies, meshIndicies)
        zox_sys_o(MeshVertices, meshVertices)
        zox_sys_o(MeshColorRGBs, meshColorRGBs)
        if (chunkMeshDirty->value != chunk_dirty_state_update) {
            continue;
        }
        if (!colorRGBs->length) {
            zox_logw("vox has no colors");
            continue;
        }
        // removes mesh when 255
        clear_mesh(meshIndicies, meshVertices, meshColorRGBs);
        if (renderLod->value < 254) {
            const byte max_depth = nodeDepth->value;
            const VoxelNode *chunk_left = chunkNeighbors->value[0] == 0 ? NULL : zox_get(chunkNeighbors->value[0], VoxelNode)
            const VoxelNode *chunk_right = chunkNeighbors->value[1] == 0 ? NULL : zox_get(chunkNeighbors->value[1], VoxelNode)
            const VoxelNode *chunk_down = chunkNeighbors->value[2] == 0 ? NULL : zox_get(chunkNeighbors->value[2], VoxelNode)
            const VoxelNode *chunk_up = chunkNeighbors->value[3] == 0 ? NULL : zox_get(chunkNeighbors->value[3], VoxelNode)
            const VoxelNode *chunk_back = chunkNeighbors->value[4] == 0 ? NULL : zox_get(chunkNeighbors->value[4], VoxelNode)
            const VoxelNode *chunk_front = chunkNeighbors->value[5] == 0 ? NULL : zox_get(chunkNeighbors->value[5], VoxelNode)
            const VoxelNode *neighbors[] =  { chunk_left, chunk_right, chunk_down, chunk_up, chunk_back, chunk_front };
            const byte chunk_left_max_distance = chunkNeighbors->value[0] == 0 ? 0 : zox_get_value(chunkNeighbors->value[0], RenderLod)
            const byte chunk_right_max_distance = chunkNeighbors->value[1] == 0 ? 0 : zox_get_value(chunkNeighbors->value[1], RenderLod)
            const byte chunk_down_max_distance = chunkNeighbors->value[2] == 0 ? 0 : zox_get_value(chunkNeighbors->value[2], RenderLod)
            const byte chunk_up_max_distance = chunkNeighbors->value[3] == 0 ? 0 : zox_get_value(chunkNeighbors->value[3], RenderLod)
            const byte chunk_back_max_distance = chunkNeighbors->value[4] == 0 ? 0 : zox_get_value(chunkNeighbors->value[4], RenderLod)
            const byte chunk_front_max_distance = chunkNeighbors->value[5] == 0 ? 0 : zox_get_value(chunkNeighbors->value[5], RenderLod)
            byte neighbor_lods[6];
            neighbor_lods[0] = get_chunk_division_from_lod(chunk_left_max_distance, max_depth);
            neighbor_lods[1] = get_chunk_division_from_lod(chunk_right_max_distance, max_depth);
            neighbor_lods[2] = get_chunk_division_from_lod(chunk_down_max_distance, max_depth);
            neighbor_lods[3] = get_chunk_division_from_lod(chunk_up_max_distance, max_depth);
            neighbor_lods[4] = get_chunk_division_from_lod(chunk_back_max_distance, max_depth);
            neighbor_lods[5] = get_chunk_division_from_lod(chunk_front_max_distance, max_depth);
            const float3 total_mesh_offset = float3_scale(calculate_vox_bounds(chunkSize->value, voxScale->value), -1);
            const byte chunk_depth = get_chunk_division_from_lod(renderLod->value, max_depth);
            build_node_mesh_colors(
                voxelNode,
                colorRGBs,
                meshIndicies,
                meshVertices,
                meshColorRGBs,
                chunk_depth,
                neighbors,
                neighbor_lods,
                total_mesh_offset,
                voxScale->value);
        }
        meshDirty->value = mesh_state_trigger_slow;
    }
} zox_declare_system(ChunkColorsBuildSystem)