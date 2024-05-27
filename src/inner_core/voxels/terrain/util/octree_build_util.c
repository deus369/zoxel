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
    add_voxel_face_uvs_indicies(0)
    add_voxel_face_uvs_indicies(1)
    add_voxel_face_uvs_indicies(2)
    add_voxel_face_uvs_indicies(3)
    add_voxel_face_uvs_indicies(4)
    add_voxel_face_uvs_indicies(5)
    mesh_data->indicies->size += voxel_face_indicies_length;
    expand_capacity_float3_array_d(mesh_data->vertices, voxel_face_vertices_length);
    zox_build_voxel_face_vert(0)
    zox_build_voxel_face_vert(1)
    zox_build_voxel_face_vert(2)
    zox_build_voxel_face_vert(3)
    mesh_data->vertices->size += voxel_face_vertices_length;
    expand_capacity_float2_array_d(mesh_data->uvs, voxel_face_vertices_length);
    add_voxel_face_uvs_uvs(0)
    add_voxel_face_uvs_uvs(1)
    add_voxel_face_uvs_uvs(2)
    add_voxel_face_uvs_uvs(3)
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

void build_if_adjacent_voxel(const ChunkOctree *root_node, const ChunkOctree *parent_node, const float3 vertex_position_offset, const int* voxel_face_indicies, const float3 *voxel_face_vertices, const float2 *voxel_uvs, const unsigned char voxel_direction, const ChunkOctree *neighbors[], const unsigned char *neighbor_lods, const unsigned char distance_to_camera, const unsigned char node_index, const byte3 node_position, const unsigned char depth, const unsigned char lod, const unsigned char voxel, const float octree_scale, const float vert_scale, int3 octree_position, const mesh_uvs_build_data *mesh_data, const unsigned char *voxel_solidity) {
    if (is_adjacent_all_solid(voxel_direction, root_node, parent_node, neighbors, octree_position, node_index, node_position, depth, lod, neighbor_lods, edge_voxel, voxel_solidity)) return;
    unsigned char is_regular_build = 1;
    if (zox_build_all_faces && distance_to_camera <= high_resolution_terain_lod) {
        /* so far just increasing face draw resolution for up faces */
        if (voxel_direction == direction_up) {
            int depth_difference = max_octree_depth - depth;
            if (depth_difference != 0) {
                is_regular_build = 0;
                /* this checks per voxel position if voxel is solid next to it */
                int3 scaled_octree_position = octree_position;
                const int amplify_position = pow(2, depth_difference);
                if (amplify_position != 1) int3_multiply_int_p(&scaled_octree_position, amplify_position);
                int3 local_node_position = int3_zero;
                local_node_position.y = (octree_scale - 1); // place at top of current scale building
                for (local_node_position.x = 0; local_node_position.x < octree_scale; local_node_position.x++) {
                    for (local_node_position.z = 0; local_node_position.z < octree_scale; local_node_position.z++) {
                        int3 global_octree_position = scaled_octree_position;
                        int3_add_int3(&global_octree_position, local_node_position);
                        if (is_adjacent_solid(voxel_direction, root_node, neighbors, global_octree_position, max_octree_depth, edge_voxel, voxel_solidity)) continue;
                        // remember: vertex offset is just node position / voxel position
                        zox_build_voxel_face(mesh_data, voxel, voxel_face_indicies, voxel_face_vertices, voxel_uvs, voxel_direction, float3_from_int3(global_octree_position), vert_scale);
                    }
                }
            }
        }
    }
    if (is_regular_build) {
        zox_build_voxel_face(mesh_data, voxel, voxel_face_indicies, voxel_face_vertices, voxel_uvs, voxel_direction, vertex_position_offset, octree_scale * vert_scale);
    }
}

// if building, build
#define zox_build_if_adjacent_voxel(direction_name, is_positive, voxel_uvs)\
    build_if_adjacent_voxel(root_node, parent_node, vertex_position_offset, get_voxel_indices(is_positive), voxel_face_vertices##_##direction_name, voxel_uvs, direction##_##direction_name, neighbors, neighbor_lods, distance_to_camera, node_index, node_position, depth, lod, voxel, octree_scale, vert_scale, octree_position, mesh_data, voxel_solidity);

// if child node is solid, dig down
#define zox_terrain_building_dig_node(i)\
    if (chunk_octree->nodes[i].value) {\
        zox_terrain_building_dig(root_node, tilemapUVs, chunk_octree, &chunk_octree->nodes[i], neighbors, neighbor_lods, mesh_data, distance_to_camera, lod, depth, int3_add(octree_position, octree_positions[i]), i, old_octree_scale, vert_scale, voxel_solidity, voxel_uv_indexes);\
    }

void zox_terrain_building_dig(const ChunkOctree *root_node, const TilemapUVs *tilemapUVs, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree, const ChunkOctree *neighbors[], const unsigned char *neighbor_lods, const mesh_uvs_build_data *mesh_data, const unsigned char distance_to_camera, const unsigned char lod, unsigned char depth, int3 octree_position, const unsigned char node_index, const float old_octree_scale, const float vert_scale, const unsigned char *voxel_solidity, const int *voxel_uv_indexes) {
    if (depth >= lod || chunk_octree->nodes == NULL) {
        if (chunk_octree->value != 0 && voxel_solidity[chunk_octree->value - 1]) { //  (chunk_octree->value)
            const unsigned char voxel = chunk_octree->value;
            const float octree_scale = octree_scales3[depth];
            const float3 vertex_position_offset = float3_from_int3(octree_position);
            const byte3 node_position = octree_positions_b[node_index];
            // const float2 *voxel_uvs = &tilemapUVs->value[(voxel - 1) * 4];
            // &tilemapUVs->value[voxel_uv_indexes[(voxel - 1) * 6 + 0]]
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
        zox_terrain_building_dig_node(0)
        zox_terrain_building_dig_node(1)
        zox_terrain_building_dig_node(2)
        zox_terrain_building_dig_node(3)
        zox_terrain_building_dig_node(4)
        zox_terrain_building_dig_node(5)
        zox_terrain_building_dig_node(6)
        zox_terrain_building_dig_node(7)
    }
}

void build_chunk_octree_mesh_uvs(const ChunkOctree *chunk_octree, const TilemapUVs *tilemapUVs, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs, MeshColorRGBs *meshColorRGBs, const unsigned char distance_to_camera, const unsigned char lod, const ChunkOctree *neighbors[], const unsigned char *neighbor_lods, const float vert_scale, const unsigned char *voxel_solidity, const int *voxel_uv_indexes) {
    int_array_d* indicies = create_int_array_d(initial_dynamic_array_size);
    float3_array_d* vertices = create_float3_array_d(initial_dynamic_array_size);
    float2_array_d* uvs = create_float2_array_d(initial_dynamic_array_size);
    color_rgb_array_d* color_rgbs = create_color_rgb_array_d(initial_dynamic_array_size);
    const mesh_uvs_build_data mesh_data = { indicies, vertices, uvs, color_rgbs };
    zox_terrain_building_dig(chunk_octree, tilemapUVs, NULL, chunk_octree, neighbors, neighbor_lods, &mesh_data, distance_to_camera, lod, 0, int3_zero, 0, 1, vert_scale, voxel_solidity, voxel_uv_indexes);
    clear_mesh_uvs(meshIndicies, meshVertices, meshColorRGBs, meshUVs);
    meshIndicies->length = indicies->size;
    meshVertices->length = vertices->size;
    meshUVs->length = uvs->size;
    meshColorRGBs->length = color_rgbs->size;
    meshIndicies->value = finalize_int_array_d(indicies);
    meshVertices->value = finalize_float3_array_d(vertices);
    meshColorRGBs->value = finalize_color_rgb_array_d(color_rgbs);
    meshUVs->value = finalize_float2_array_d(uvs);
    on_memory_component_created(meshIndicies, MeshIndicies)
    on_memory_component_created(meshVertices, MeshVertices)
    on_memory_component_created(meshColorRGBs, MeshColorRGBs)
    on_memory_component_created(meshUVs, MeshUVs)
}

#define set_neightbor_chunk_data(dir) {\
    const unsigned char index = direction##_##dir;\
    const ecs_entity_t neighbor = chunkNeighbors2->value[index];\
    const ChunkOctree *neighbor_chunk = neighbor == 0 ? NULL : ecs_get(world, neighbor, ChunkOctree);\
    const unsigned char neighbor_distance = neighbor == 0 ? 0 : ecs_get(world, neighbor, RenderLod)->value;\
    neighbor_lods[index] = get_terrain_lod_from_camera_distance(neighbor_distance);\
    neighbors[index] = neighbor_chunk;\
}
