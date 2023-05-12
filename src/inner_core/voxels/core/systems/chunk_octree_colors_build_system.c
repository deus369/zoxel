unsigned char colors_get_max_depth_from_division(unsigned char chunk_division) {
    unsigned char max_depth = max_octree_depth;
    return max_depth;
}

#define add_voxel_face_colors_indicies(index)\
    indicies->data[indicies->size + index] = vertices->size + voxel_face_indicies[index];

#define add_voxel_face_colors_vertices(index) {\
    float3 vertex_position = voxel_face_vertices[index];\
    float3_multiply_float_p(&vertex_position, voxel_scale);\
    float3_add_float3_p(&vertex_position, vertex_position_offset);\
    vertices->data[vertices->size + index] = vertex_position;\
}

// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset
void add_voxel_face_colors_d(int_array_d *indicies, float3_array_d* vertices, color_rgb_array_d* color_rgbs,
    float3 vertex_position_offset, color_rgb voxel_color, float voxel_scale,
    const int* voxel_face_indicies, const float3 voxel_face_vertices[], unsigned char direction) {
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

#define zoxel_octree_colors_build_face_d(direction_name, is_positive)\
if (!is_adjacent_all_solid(direction##_##direction_name, root_node, parent_node, neighbors,\
    octree_position, node_index, node_position, depth, max_depth, neighbors_max_depths, 0)) {\
    add_voxel_face_colors_d(indicies, vertices, color_rgbs, vertex_position_offset, voxel_color,\
        voxel_scale, get_voxel_indices(is_positive), voxel_face_vertices##_##direction_name,\
        direction##_##direction_name);\
}

#define build_octree_chunk_colors_child_node(i)\
if (chunk_octree->nodes[i].value != 0) {\
    build_octree_chunk_colors_d(root_node, chunk_octree, &chunk_octree->nodes[i], neighbors, neighbors_max_depths,\
        colorRGBs, indicies, vertices, color_rgbs, max_depth, depth, int3_add(octree_position, octree_positions[i]), i, total_mesh_offset);\
}

void build_octree_chunk_colors_d(const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree,
    const ChunkOctree *neighbors[], const unsigned char *neighbors_max_depths, const ColorRGBs *colorRGBs,
    int_array_d *indicies, float3_array_d* vertices, color_rgb_array_d* color_rgbs,
    const unsigned char max_depth, unsigned char depth, int3 octree_position, const unsigned char node_index,
    float3 total_mesh_offset) {
    if (depth >= max_depth || chunk_octree->nodes == NULL) {
        // zoxel_log(" - deepest depth [%i]\n", chunk_octree->value);
        if (chunk_octree->value != 0) {
            float voxel_scale = octree_scales3[depth] * model_scale;
            float3 vertex_position_offset = {
                total_mesh_offset.x + octree_position.x * voxel_scale,
                total_mesh_offset.y + octree_position.y * voxel_scale,
                total_mesh_offset.z + octree_position.z * voxel_scale }; //float3_from_int3(octree_position);
            byte3 node_position = octree_positions_b[node_index];
            unsigned char voxel = chunk_octree->value;
            color_rgb voxel_color = colorRGBs->value[voxel - 1];
            // zoxel_log(" - voxel_color [%ix%ix%i]\n", voxel_color.r, voxel_color.g, voxel_color.b);
            zoxel_octree_colors_build_face_d(left, 0)
            zoxel_octree_colors_build_face_d(right, 1)
            zoxel_octree_colors_build_face_d(down, 1)
            zoxel_octree_colors_build_face_d(up, 0)
            zoxel_octree_colors_build_face_d(back, 0)
            zoxel_octree_colors_build_face_d(front, 1)
        }
    } else {
        // zoxel_log(" - increasing depth [%i]\n", depth);
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        build_octree_chunk_colors_child_node(0)
        build_octree_chunk_colors_child_node(1)
        build_octree_chunk_colors_child_node(2)
        build_octree_chunk_colors_child_node(3)
        build_octree_chunk_colors_child_node(4)
        build_octree_chunk_colors_child_node(5)
        build_octree_chunk_colors_child_node(6)
        build_octree_chunk_colors_child_node(7)
    }
}

void build_chunk_octree_mesh_colors(const ChunkOctree *chunk_octree, const ColorRGBs *colorRGBs,
    MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshColorRGBs *meshColorRGBs,
    unsigned char chunk_division, const ChunkOctree *neighbors[], unsigned char *neighbors_max_depths,
    float3 total_mesh_offset) {
    unsigned char max_depth = colors_get_max_depth_from_division(chunk_division);
    int_array_d* indicies = create_int_array_d();
    float3_array_d* vertices = create_float3_array_d();
    color_rgb_array_d* color_rgbs = create_color_rgb_array_d();
    build_octree_chunk_colors_d(chunk_octree, NULL, chunk_octree, neighbors, neighbors_max_depths, colorRGBs,
        indicies, vertices, color_rgbs, max_depth, 0, int3_zero, 0, total_mesh_offset);
    if (meshIndicies->length != 0) free(meshIndicies->value);
    if (meshVertices->length != 0) free(meshVertices->value);
    if (meshColorRGBs->length != 0) free(meshColorRGBs->value);
    meshIndicies->length = indicies->size;
    meshVertices->length = vertices->size;
    meshColorRGBs->length = color_rgbs->size;
    meshIndicies->value = finalize_int_array_d(indicies);
    meshVertices->value = finalize_float3_array_d(vertices);
    meshColorRGBs->value = finalize_color_rgb_array_d(color_rgbs);
}

void ChunkOctreeColorsBuildSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(it->ctx, NULL)) return;
    #ifdef zoxel_time_octree_chunk_builds_system
        begin_timing()
    #endif
    int chunks_built = 0;
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 1);
    const ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 2);
    const ChunkDivision *chunkDivisions = ecs_field(it, ChunkDivision, 3);
    const ChunkNeighbors *chunkNeighbors = ecs_field(it, ChunkNeighbors, 4);
    const ColorRGBs *colorRGBs = ecs_field(it, ColorRGBs, 5);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 6);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 7);
    MeshColorRGBs *meshColorRGBs = ecs_field(it, MeshColorRGBs, 8);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 9);
    // zoxel_log(" > building color chunk octrees [%i]\n", it->count);
    for (int i = 0; i < it->count; i++) {
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value != 1) continue;
        MeshDirty *meshDirty = &meshDirtys[i];
        const ChunkOctree *chunkOctree = &chunkOctrees[i];
        const ChunkDivision *chunkDivision = &chunkDivisions[i];
        const ChunkNeighbors *chunkNeighbors2 = &chunkNeighbors[i];
        const ColorRGBs *colorRGBs2 = &colorRGBs[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        MeshColorRGBs *meshColorRGBs2 = &meshColorRGBs[i];
        const ChunkOctree *chunk_left = chunkNeighbors2->value[0] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[0], ChunkOctree);
        const ChunkOctree *chunk_right = chunkNeighbors2->value[1] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[1], ChunkOctree);
        const ChunkOctree *chunk_down = chunkNeighbors2->value[2] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[2], ChunkOctree);
        const ChunkOctree *chunk_up = chunkNeighbors2->value[3] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[3], ChunkOctree);
        const ChunkOctree *chunk_back = chunkNeighbors2->value[4] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[4], ChunkOctree);
        const ChunkOctree *chunk_front = chunkNeighbors2->value[5] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[5], ChunkOctree);
        const ChunkOctree *neighbors[] =  { chunk_left, chunk_right, chunk_down, chunk_up, chunk_back, chunk_front };
        unsigned char chunk_left_max_distance = chunkNeighbors2->value[0] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[0], ChunkDivision)->value;
        unsigned char chunk_right_max_distance = chunkNeighbors2->value[1] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[1], ChunkDivision)->value;
        unsigned char chunk_down_max_distance = chunkNeighbors2->value[2] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[2], ChunkDivision)->value;
        unsigned char chunk_up_max_distance = chunkNeighbors2->value[3] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[3], ChunkDivision)->value;
        unsigned char chunk_back_max_distance = chunkNeighbors2->value[4] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[4], ChunkDivision)->value;
        unsigned char chunk_front_max_distance = chunkNeighbors2->value[5] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[5], ChunkDivision)->value;
        unsigned char *neighbors_max_depths = malloc(6);
        neighbors_max_depths[0] = colors_get_max_depth_from_division(chunk_left_max_distance);
        neighbors_max_depths[1] = colors_get_max_depth_from_division(chunk_right_max_distance);
        neighbors_max_depths[2] = colors_get_max_depth_from_division(chunk_down_max_distance);
        neighbors_max_depths[3] = colors_get_max_depth_from_division(chunk_up_max_distance);
        neighbors_max_depths[4] = colors_get_max_depth_from_division(chunk_back_max_distance);
        neighbors_max_depths[5] = colors_get_max_depth_from_division(chunk_front_max_distance);
        int chunk_length = powers_of_two_byte[5];
        int3 chunk_size = (int3) { chunk_length, chunk_length, chunk_length };
        float3 total_mesh_offset = calculate_vox_bounds(chunk_size);
        float3_multiply_float_p(&total_mesh_offset, -1);
        // zoxel_log(" > mesh offset [%fx%fx%f] - [%i]\n", total_mesh_offset.x, total_mesh_offset.y, total_mesh_offset.z, chunk_length);
        build_chunk_octree_mesh_colors(chunkOctree, colorRGBs2, meshIndicies2, meshVertices2, meshColorRGBs2, chunkDivision->value, neighbors, neighbors_max_depths, total_mesh_offset);
        /*if (meshIndicies2->length != 0) {
            tri_count -= meshIndicies2->length / 3;
        }
        if (meshIndicies2->length != 0) {
            tri_count += meshIndicies2->length / 3;
        }*/
        chunkDirty->value = 0;
        meshDirty->value = 1;
        free(neighbors_max_depths);
        // time_cycle_end("       - octree_chunk_build_cycle")
        chunks_built++;
        // zoxel_log("     + built chunk octree colors - indicies[%i]\n", meshIndicies2->length);
        // if (chunks_built >= max_chunks_build_per_frame) break;
        #ifdef zoxel_time_octree_chunk_builds_system
            did_do_timing()
        #endif
    }
    #ifdef zoxel_time_octree_chunk_builds_system
        end_timing_cutoff("    - octree_chunk_build_system", zoxel_time_octree_chunk_builds_system_cutoff)
    #endif
}
zoxel_declare_system(ChunkOctreeColorsBuildSystem)