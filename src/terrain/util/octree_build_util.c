// #define zox_octree_chunk_build_limits
const unsigned char zox_build_all_faces = 1;

#ifndef zox_disable_hidden_terrain_edge
    const unsigned char edge_voxel = 1;
#else
    const unsigned char edge_voxel = 0;
#endif

#define add_voxel_face_uvs_indicies(index) mesh_data->indicies->data[mesh_data->indicies->size + index] = mesh_data->vertices->size + voxel_face_indicies[index];

#define add_voxel_face_uvs_uvs(index) mesh_data->uvs->data[mesh_data->uvs->size + index] = voxel_face_uvs[index];

#define zox_build_voxel_face_vert(index) {\
    float3 vertex_position = voxel_face_vertices[index];\
    float3_add_float3_p(&vertex_position, offset);\
    float3_multiply_float_p(&vertex_position, vert_scale);\
    mesh_data->vertices->data[mesh_data->vertices->size + index] = vertex_position;\
}

// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset
void zox_build_voxel_face(const mesh_uvs_build_data *mesh_data, const unsigned char voxel, const int* voxel_face_indicies, const float3 voxel_face_vertices[], const float2 *voxel_face_uvs, const unsigned char direction, const float3 offset, const float vert_scale) {
    expand_capacity_int_array_d(mesh_data->indicies, voxel_face_indicies_length);
    for (unsigned char i = 0; i < 6; i++) {
        add_voxel_face_uvs_indicies(i)
    }
    mesh_data->indicies->size += voxel_face_indicies_length;
    expand_capacity_float3_array_d(mesh_data->vertices, voxel_face_vertices_length);
    for (unsigned char i = 0; i < 4; i++) {
        zox_build_voxel_face_vert(i)
    }
    mesh_data->vertices->size += voxel_face_vertices_length;
    expand_capacity_float2_array_d(mesh_data->uvs, voxel_face_vertices_length);
    for (unsigned char i = 0; i < 4; i++) {
        add_voxel_face_uvs_uvs(i)
    }
    mesh_data->uvs->size += voxel_face_vertices_length;
    for (unsigned char a = 0; a < voxel_face_vertices_length; a++) {
        color_rgb vertex_color = color_rgb_white;
#ifndef zox_disable_fake_voxel_lighting
        if (direction == direction_down) color_rgb_multiply_float(&vertex_color, 0.33f);
        else if (direction == direction_front) color_rgb_multiply_float(&vertex_color, 0.44f);
        else if (direction == direction_left) color_rgb_multiply_float(&vertex_color, 0.55f);
        else if (direction == direction_back) color_rgb_multiply_float(&vertex_color, 0.66f);
        else if (direction == direction_right) color_rgb_multiply_float(&vertex_color, 0.76f);
#endif
        add_to_color_rgb_array_d(mesh_data->color_rgbs, vertex_color);
    }
}

// this function accounts for size of drawing voxels
void build_if_adjacent_voxel(const ChunkOctree *root_node, const ChunkOctree *parent_node, const float3 vertex_position_offset, const int* voxel_face_indicies, const float3 *voxel_face_vertices, const float2 *voxel_uvs, const unsigned char voxel_direction, const ChunkOctree *neighbors[], const unsigned char neighbor_depths[], const unsigned char is_max_depth_chunk, const unsigned char node_index, const byte3 node_position, const unsigned char depth, const unsigned char lod, const unsigned char voxel, const float octree_scale, const float vert_scale, int3 octree_position, const mesh_uvs_build_data *mesh_data, const unsigned char *voxel_solidity) {
    if (is_adjacent_all_solid(voxel_direction, root_node, parent_node, neighbors, octree_position, node_index, node_position, depth, lod, neighbor_depths, edge_voxel, voxel_solidity)) return;
    unsigned char is_regular_build = 1;
    if (zox_build_all_faces && is_max_depth_chunk) {
        /* so far just increasing face draw resolution for up faces */
        // if (voxel_direction == direction_up) {
            int depth_difference = max_octree_depth - depth;
            if (depth_difference != 0) {
                is_regular_build = 0;
                /* this checks per voxel position if voxel is solid next to it */
                int3 scaled_octree_position = octree_position;
                const int amplify_position = pow(2, depth_difference);
                if (amplify_position != 1) int3_multiply_int_p(&scaled_octree_position, amplify_position);
                int3 local_node_position = int3_zero;

                if (voxel_direction == direction_up) local_node_position.y = (octree_scale - 1); // place at top of current scale building
                else if (voxel_direction == direction_right) local_node_position.x = (octree_scale - 1);
                else if (voxel_direction == direction_front) local_node_position.z = (octree_scale - 1);

                if (voxel_direction == direction_up || voxel_direction == direction_down) { // y
                    for (local_node_position.x = 0; local_node_position.x < octree_scale; local_node_position.x++) {
                        for (local_node_position.z = 0; local_node_position.z < octree_scale; local_node_position.z++) {
                            int3 global_octree_position = scaled_octree_position;
                            int3_add_int3(&global_octree_position, local_node_position);
                            if (is_adjacent_solid(voxel_direction, root_node, neighbors, global_octree_position, max_octree_depth, edge_voxel, voxel_solidity)) continue;
                            // remember: vertex offset is just node position / voxel position
                            zox_build_voxel_face(mesh_data, voxel, voxel_face_indicies, voxel_face_vertices, voxel_uvs, voxel_direction, float3_from_int3(global_octree_position), vert_scale);
                        }
                    }
                } else if (voxel_direction == direction_left || voxel_direction == direction_right) { // x
                    for (local_node_position.y = 0; local_node_position.y < octree_scale; local_node_position.y++) {
                        for (local_node_position.z = 0; local_node_position.z < octree_scale; local_node_position.z++) {
                            int3 global_octree_position = scaled_octree_position;
                            int3_add_int3(&global_octree_position, local_node_position);
                            if (is_adjacent_solid(voxel_direction, root_node, neighbors, global_octree_position, max_octree_depth, edge_voxel, voxel_solidity)) continue;
                            // remember: vertex offset is just node position / voxel position
                            zox_build_voxel_face(mesh_data, voxel, voxel_face_indicies, voxel_face_vertices, voxel_uvs, voxel_direction, float3_from_int3(global_octree_position), vert_scale);
                        }
                    }
                } else { // z
                    for (local_node_position.x = 0; local_node_position.x < octree_scale; local_node_position.x++) {
                        for (local_node_position.y = 0; local_node_position.y < octree_scale; local_node_position.y++) {
                            int3 global_octree_position = scaled_octree_position;
                            int3_add_int3(&global_octree_position, local_node_position);
                            if (is_adjacent_solid(voxel_direction, root_node, neighbors, global_octree_position, max_octree_depth, edge_voxel, voxel_solidity)) continue;
                            // remember: vertex offset is just node position / voxel position
                            zox_build_voxel_face(mesh_data, voxel, voxel_face_indicies, voxel_face_vertices, voxel_uvs, voxel_direction, float3_from_int3(global_octree_position), vert_scale);
                        }
                    }
                }
            // }
        }
    }
    if (is_regular_build) {
        zox_build_voxel_face(mesh_data, voxel, voxel_face_indicies, voxel_face_vertices, voxel_uvs, voxel_direction, vertex_position_offset, octree_scale * vert_scale);
    }
}

// if building, build
#define zox_build_if_adjacent_voxel(direction_name, is_positive, voxel_uvs)\
    build_if_adjacent_voxel(root_node, parent_node, vertex_position_offset, get_voxel_indicies_##is_positive, voxel_face_vertices##_##direction_name, voxel_uvs, direction##_##direction_name, neighbors, neighbor_depths, is_max_depth_chunk, node_index, node_position, depth, lod, voxel, octree_scale, vert_scale, octree_position, mesh_data, voxel_solidity);

// if child node is solid, dig down
#define zox_terrain_building_dig_node(i)\
    if (chunk_octree->nodes[i].value) {\
        zox_terrain_building_dig(root_node, tilemapUVs, chunk_octree, &chunk_octree->nodes[i], neighbors, neighbor_depths, mesh_data, is_max_depth_chunk, lod, depth, int3_add(octree_position, octree_positions[i]), i, old_octree_scale, vert_scale, voxel_solidity, voxel_uv_indexes);\
    }

void zox_terrain_building_dig(const ChunkOctree *root_node, const TilemapUVs *tilemapUVs, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree, const ChunkOctree *neighbors[], const unsigned char neighbor_depths[], const mesh_uvs_build_data *mesh_data, const unsigned char is_max_depth_chunk, const unsigned char lod, unsigned char depth, int3 octree_position, const unsigned char node_index, const float old_octree_scale, const float vert_scale, const unsigned char *voxel_solidity, const int *voxel_uv_indexes) {
    if (depth >= lod || chunk_octree->nodes == NULL) {
        if (chunk_octree->value != 0 && voxel_solidity[chunk_octree->value - 1]) {
            const unsigned char voxel = chunk_octree->value;
            const float octree_scale = octree_scales3[depth];
            const float3 vertex_position_offset = float3_from_int3(octree_position);
            const byte3 node_position = octree_positions_b[node_index];
            const int voxel_uvs_index = (voxel - 1) * 6;
            zox_build_if_adjacent_voxel(left, 0, &tilemapUVs->value[voxel_uv_indexes[voxel_uvs_index + 0]])
            zox_build_if_adjacent_voxel(right, 1, &tilemapUVs->value[voxel_uv_indexes[voxel_uvs_index + 1]])
            zox_build_if_adjacent_voxel(down, 1, &tilemapUVs->value[voxel_uv_indexes[voxel_uvs_index + 2]])
            zox_build_if_adjacent_voxel(up, 0, &tilemapUVs->value[voxel_uv_indexes[voxel_uvs_index + 3]])
            zox_build_if_adjacent_voxel(back, 0, &tilemapUVs->value[voxel_uv_indexes[voxel_uvs_index + 4]])
            zox_build_if_adjacent_voxel(front, 1, &tilemapUVs->value[voxel_uv_indexes[voxel_uvs_index + 5]])
        }
    } else {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        for (unsigned char i = 0; i < 8; i++) {
            zox_terrain_building_dig_node(i)
        }
    }
}

void build_chunk_terrain_mesh(const ChunkOctree *chunk_octree, const TilemapUVs *tilemapUVs, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs, MeshColorRGBs *meshColorRGBs, const unsigned char is_max_depth_chunk, const unsigned char depth, const ChunkOctree *neighbors[], const unsigned char neighbor_depths[], const float vert_scale, const unsigned char *voxel_solidity, const int *voxel_uv_indexes) {
    const mesh_uvs_build_data mesh_data = {
        .indicies = create_int_array_d(initial_dynamic_array_size),
        .vertices = create_float3_array_d(initial_dynamic_array_size),
        .uvs = create_float2_array_d(initial_dynamic_array_size),
        .color_rgbs = create_color_rgb_array_d(initial_dynamic_array_size)
    };
    // build out mesh data
    zox_terrain_building_dig(chunk_octree, tilemapUVs, NULL, chunk_octree, neighbors, neighbor_depths, &mesh_data, is_max_depth_chunk, depth, 0, int3_zero, 0, 1, vert_scale, voxel_solidity, voxel_uv_indexes);

    // sizes
    meshIndicies->length = mesh_data.indicies->size;
    meshVertices->length = mesh_data.vertices->size;
    meshUVs->length = mesh_data.uvs->size;
    meshColorRGBs->length = mesh_data.color_rgbs->size;

    // data
    meshIndicies->value = finalize_int_array_d(mesh_data.indicies);
    meshVertices->value = finalize_float3_array_d(mesh_data.vertices);
    meshColorRGBs->value = finalize_color_rgb_array_d(mesh_data.color_rgbs);
    meshUVs->value = finalize_float2_array_d(mesh_data.uvs);

    // for data statistics
    on_memory_component_created(meshIndicies, MeshIndicies)
    on_memory_component_created(meshVertices, MeshVertices)
    on_memory_component_created(meshColorRGBs, MeshColorRGBs)
    on_memory_component_created(meshUVs, MeshUVs)
}
