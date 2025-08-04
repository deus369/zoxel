// todo: remove macros, they're not useful here, debugging and maintainance bad

#define add_voxel_face_colors_indicies(index)\
    indicies->data[indicies->size + index] = vertices->size + voxel_face_indicies[index];

#define add_voxel_face_colors_vertices(index) {\
    float3 vertex_position = voxel_face_vertices[index];\
    float3_scale_p(&vertex_position, voxel_scale);\
    float3_add_float3_p(&vertex_position, vertex_position_offset);\
    vertices->data[vertices->size + index] = vertex_position;\
}

// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset
void add_voxel_face_colors_d(
    int_array_d *indicies,
    float3_array_d* vertices,
    color_rgb_array_d* color_rgbs,
    float3 vertex_position_offset,
    color_rgb voxel_color,
    const float voxel_scale,
    const int* voxel_face_indicies,
    const float3 voxel_face_vertices[],
    const byte direction
) {
    expand_capacity_int_array_d(indicies, voxel_face_indicies_length);
        add_voxel_face_colors_indicies(0)
        add_voxel_face_colors_indicies(1)
        add_voxel_face_colors_indicies(2)
        add_voxel_face_colors_indicies(3)
        add_voxel_face_colors_indicies(4)
        add_voxel_face_colors_indicies(5)
    indicies->size += voxel_face_indicies_length;
    expand_capacity_float3_array_d(vertices, voxel_face_vertices_length);
        add_voxel_face_colors_vertices(0)
        add_voxel_face_colors_vertices(1)
        add_voxel_face_colors_vertices(2)
        add_voxel_face_colors_vertices(3)
    vertices->size += voxel_face_vertices_length;
    for (int a = 0; a < voxel_face_vertices_length; a++) {
        color_rgb vertex_color = voxel_color;
#ifndef zox_disable_fake_voxel_lighting
        if (direction == direction_down) {
            color_rgb_multiply_float(&vertex_color, 0.33f);
        } else if (direction == direction_front) color_rgb_multiply_float(&vertex_color, 0.44f);
        else if (direction == direction_left) color_rgb_multiply_float(&vertex_color, 0.55f);
        else if (direction == direction_back) color_rgb_multiply_float(&vertex_color, 0.66f);
        else if (direction == direction_right) color_rgb_multiply_float(&vertex_color, 0.76f);
#endif
        add_to_color_rgb_array_d(color_rgbs, vertex_color);
    }
}

#define zoxel_octree_colors_build_face_d(direction_name, is_positive, face_verts)\
if (!is_adjacent_all_solid( \
    NULL, \
    color_edge_voxel, \
    neighbors, \
    neighbor_lods, \
    root_node, \
    octree_position, \
    direction##_##direction_name, \
    depth \
)) {\
    add_voxel_face_colors_d(indicies, vertices, color_rgbs, vertex_position_offset, voxel_color, voxel_scale, get_voxel_indicies_##is_positive, face_verts, direction##_##direction_name);\
}

void build_octree_chunk_colors_d(
    const VoxelNode* root_node,
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
    int3 octree_position,
    const byte node_index,
    const float3 total_mesh_offset,
    const float vox_scale) {
    if (node == NULL) {
        return;
    }
    if (depth >= max_depth || is_closed_VoxelNode(node)) {
        const byte voxel = node->value;
        if (voxel) {
            const byte voxel_index = voxel - 1;
            if (voxel_index >= colorRGBs->length) {
                // warning here?
                return;
            }
            const color_rgb voxel_color = colorRGBs->value[voxel_index];
            const float voxel_scale = real_chunk_scale * octree_scales3[depth] * vox_scale;
            float3 vertex_position_offset = float3_from_int3(octree_position);
            float3_scale_p(&vertex_position_offset, voxel_scale);
            float3_add_float3_p(&vertex_position_offset, total_mesh_offset);
            byte3 node_position = octree_positions_b[node_index];
            zoxel_octree_colors_build_face_d(left, 0, voxel_face_vertices_n[0])
            zoxel_octree_colors_build_face_d(right, 1, voxel_face_vertices_n[1])
            zoxel_octree_colors_build_face_d(down, 1, voxel_face_vertices_n[2])
            zoxel_octree_colors_build_face_d(up, 0, voxel_face_vertices_n[3])
            zoxel_octree_colors_build_face_d(back, 0, voxel_face_vertices_n[4])
            zoxel_octree_colors_build_face_d(front, 1, voxel_face_vertices_n[5])
        }
    } else {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        VoxelNode* kids = get_children_VoxelNode(node);
        for (byte i = 0; i < octree_length; i++) {
            build_octree_chunk_colors_d(
                root_node,
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
                int3_add(octree_position, octree_positions[i]),
                i,
                total_mesh_offset,
                vox_scale);
        }
    }
}

// basically it goes downwards even if upper value nodes are air
// so with our optimizing somewhere it messed up and set the upper ones to zero? idk
// or maybe it was optimized properly


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