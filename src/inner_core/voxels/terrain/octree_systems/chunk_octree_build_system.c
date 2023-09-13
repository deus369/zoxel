// #define zox_octree_chunk_build_limits
const unsigned char zox_build_all_faces = 1;

#ifndef zox_disable_hidden_terrain_edge
    const unsigned char edge_voxel = 1;
#else
    const unsigned char edge_voxel = 0;
#endif

#define add_voxel_face_uvs_indicies(index) indicies->data[indicies->size + index] = vertices->size + voxel_face_indicies[index];

#define add_voxel_face_uvs_uvs(index) uvs->data[uvs->size + index] = voxel_face_uvs[index];

#define zox_build_voxel_face_vert(index) {\
    float3 vertex_position = voxel_face_vertices[index];\
    float3_multiply_float_p(&vertex_position, voxel_scale);\
    float3_add_float3_p(&vertex_position, offset);\
    vertices->data[vertices->size + index] = vertex_position;\
}

// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset
void zox_build_voxel_face(int_array_d *indicies, float3_array_d* vertices, float2_array_d* uvs, color_rgb_array_d* color_rgbs, float3 offset, unsigned char voxel, float voxel_scale, const int* voxel_face_indicies, const float3 voxel_face_vertices[], const float2 *voxel_face_uvs, unsigned char direction) {
    expand_capacity_int_array_d(indicies, voxel_face_indicies_length);
        add_voxel_face_uvs_indicies(0)
        add_voxel_face_uvs_indicies(1)
        add_voxel_face_uvs_indicies(2)
        add_voxel_face_uvs_indicies(3)
        add_voxel_face_uvs_indicies(4)
        add_voxel_face_uvs_indicies(5)
    indicies->size += voxel_face_indicies_length;
    expand_capacity_float3_array_d(vertices, voxel_face_vertices_length);
        zox_build_voxel_face_vert(0)
        zox_build_voxel_face_vert(1)
        zox_build_voxel_face_vert(2)
        zox_build_voxel_face_vert(3)
    vertices->size += voxel_face_vertices_length;
    expand_capacity_float2_array_d(uvs, voxel_face_vertices_length);
        add_voxel_face_uvs_uvs(0)
        add_voxel_face_uvs_uvs(1)
        add_voxel_face_uvs_uvs(2)
        add_voxel_face_uvs_uvs(3)
    uvs->size += voxel_face_vertices_length;
    for (unsigned char a = 0; a < voxel_face_vertices_length; a++) {
        color_rgb vertex_color = color_rgb_white;
        if (direction == direction_down) color_rgb_multiply_float(&vertex_color, 0.33f);
        else if (direction == direction_front) color_rgb_multiply_float(&vertex_color, 0.44f);
        else if (direction == direction_left) color_rgb_multiply_float(&vertex_color, 0.55f);
        else if (direction == direction_back) color_rgb_multiply_float(&vertex_color, 0.66f);
        else if (direction == direction_right) color_rgb_multiply_float(&vertex_color, 0.76f);
        add_to_color_rgb_array_d(color_rgbs, vertex_color);
    }
}

/*
if (amplify_position != 1) {\
    zoxel_log(" > depth_difference %i, amplify_position %i\n", depth_difference, amplify_position);
    zoxel_log("     - octree_position %ix%ix%i\n", octree_position.x, octree_position.y, octree_position.z);
    zoxel_log("     - octree_position2 %ix%ix%i\n", octree_position2.x, octree_position2.y, octree_position2.z);
}
zoxel_log(" === adjacent is air %ix%ix%i\n", octree_position3.x, octree_position3.y, octree_position3.z)
*/

#define zox_build_if_adjacent_voxel(direction_name, is_positive, voxel_uvs)\
if (!is_adjacent_all_solid(direction##_##direction_name, root_node, parent_node, neighbors, octree_position, node_index, node_position, depth, lod, neighbor_lods, edge_voxel)) {\
    if (zox_build_all_faces && distance_to_camera <= high_resolution_terain_lod) {\
        /* so far just increasing face draw resolution for up faces */\
        if (direction##_##direction_name == direction_up) {\
            int depth_difference = max_octree_depth - depth;\
            if (depth_difference == 0) {\
                zox_build_voxel_face(indicies, vertices, uvs, color_rgbs, vertex_position_offset, voxel,\
                    voxel_scale, get_voxel_indices(is_positive), voxel_face_vertices##_##direction_name,\
                    voxel_uvs, direction##_##direction_name);\
            } else {\
                /* this checks per voxel position if voxel is solid next to it */\
                int amplify_position = pow(2, depth_difference);\
                int3 octree_position2 = octree_position;\
                if (amplify_position != 1) int3_multiply_int_p(&octree_position2, amplify_position);\
                int3 offset2 = int3_zero;\
                offset2.y += (voxel_scale - 1);\
                for (; offset2.x < voxel_scale; offset2.x++) {\
                    for (offset2.z = 0; offset2.z < voxel_scale; offset2.z++) {\
                        int3 octree_position3 = octree_position2;\
                        int3_add_int3(&octree_position3, offset2);\
                        if (is_adjacent_solid(direction##_##direction_name, root_node, neighbors, octree_position3, max_octree_depth, edge_voxel)) continue;\
                        float3 offset3 = float3_from_int3(offset2);\
                        float3_add_float3_p(&offset3, vertex_position_offset);\
                        zox_build_voxel_face(indicies, vertices, uvs, color_rgbs, offset3, voxel, 1, get_voxel_indices(is_positive),\
                            voxel_face_vertices##_##direction_name, voxel_uvs, direction##_##direction_name);\
                    }\
                }\
            }\
        } else {\
            zox_build_voxel_face(indicies, vertices, uvs, color_rgbs, vertex_position_offset, voxel,\
                voxel_scale, get_voxel_indices(is_positive), voxel_face_vertices##_##direction_name,\
                voxel_uvs, direction##_##direction_name);\
        }\
    } else {\
        zox_build_voxel_face(indicies, vertices, uvs, color_rgbs, vertex_position_offset, voxel,\
            voxel_scale, get_voxel_indices(is_positive), voxel_face_vertices##_##direction_name,\
            voxel_uvs, direction##_##direction_name);\
    }\
}

// if child node is solid, dig down
#define zox_terrain_building_dig_node(i)\
    if (chunk_octree->nodes[i].value) {\
        zox_terrain_building_dig(root_node, tilemapUVs, chunk_octree, &chunk_octree->nodes[i], neighbors, neighbor_lods,\
            indicies, vertices, uvs, color_rgbs, distance_to_camera, lod, depth, int3_add(octree_position, octree_positions[i]), i);\
    }

void zox_terrain_building_dig(const ChunkOctree *root_node, const TilemapUVs *tilemapUVs, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree,
    const ChunkOctree *neighbors[], const unsigned char *neighbor_lods, int_array_d *indicies, float3_array_d* vertices, float2_array_d* uvs, color_rgb_array_d* color_rgbs,
    const unsigned char distance_to_camera, const unsigned char lod, unsigned char depth, int3 octree_position, const unsigned char node_index) {
    if (depth >= lod || chunk_octree->nodes == NULL) {
        if (chunk_octree->value) {
            const unsigned char voxel = chunk_octree->value;
            float voxel_scale = octree_scales3[depth];
            float3 vertex_position_offset = float3_from_int3(octree_position);
            float3_multiply_float_p(&vertex_position_offset, voxel_scale);
            byte3 node_position = octree_positions_b[node_index];
            const float2 *voxel_uvs = &tilemapUVs->value[(voxel - 1) * 4];
            // float division_amount = get_division_amount(voxel_scale);
            // zoxel_log(" division_amount %i voxel_scale %f\n", division_amount, voxel_scale);
            zox_build_if_adjacent_voxel(left, 0, voxel_uvs)
            zox_build_if_adjacent_voxel(right, 1, voxel_uvs)
            zox_build_if_adjacent_voxel(down, 1, voxel_uvs)
            zox_build_if_adjacent_voxel(up, 0, voxel_uvs)
            zox_build_if_adjacent_voxel(back, 0, voxel_uvs)
            zox_build_if_adjacent_voxel(front, 1, voxel_uvs)
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

void build_chunk_octree_mesh_uvs(const ChunkOctree *chunk_octree, const TilemapUVs *tilemapUVs, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs, MeshColorRGBs *meshColorRGBs, unsigned char distance_to_camera, unsigned char lod, const ChunkOctree *neighbors[], unsigned char *neighbor_lods) {
    #ifndef zox_disable_voxels_dynamic_array
        int_array_d* indicies = create_int_array_d();
        float3_array_d* vertices = create_float3_array_d();
        float2_array_d* uvs = create_float2_array_d();
        color_rgb_array_d* color_rgbs = create_color_rgb_array_d();
        zox_terrain_building_dig(chunk_octree, tilemapUVs,  NULL, chunk_octree, neighbors, neighbor_lods, indicies, vertices, uvs, color_rgbs, distance_to_camera, lod, 0, int3_zero, 0);
        if (meshIndicies->length != 0) free(meshIndicies->value);
        if (meshVertices->length != 0) free(meshVertices->value);
        if (meshUVs->length != 0) free(meshUVs->value);
        if (meshColorRGBs->length != 0) free(meshColorRGBs->value);
        meshIndicies->length = indicies->size;
        meshVertices->length = vertices->size;
        meshUVs->length = uvs->size;
        meshColorRGBs->length = color_rgbs->size;
        meshIndicies->value = finalize_int_array_d(indicies);
        meshVertices->value = finalize_float3_array_d(vertices);
        meshUVs->value = finalize_float2_array_d(uvs);
        meshColorRGBs->value = finalize_color_rgb_array_d(color_rgbs);
    #else
        int2 *start = &((int2) { 0, 0 });
        count_octree_chunk(chunk_octree, NULL, chunk_octree, neighbors, neighbor_lods, meshIndicies, meshVertices, meshUVs, &mesh_count, 0, lod, int3_zero, 0, int3_zero);
        re_initialize_memory_component(meshIndicies, int, mesh_count.x);
        re_initialize_memory_component(meshVertices, float3, mesh_count.y);
        re_initialize_memory_component(meshUVs, float2, mesh_count.y);
        build_octree_chunk(chunk_octree, NULL, chunk_octree, neighbors, neighbor_lods, meshIndicies, meshVertices, meshUVs, start, 0, lod, int3_zero, 0, int3_zero);
    #endif
}

void ChunkOctreeBuildSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(it->ctx, NULL)) return;
    #ifdef zoxel_time_octree_chunk_builds_system
        begin_timing()
    #endif
    ecs_world_t *world = it->world;
    #ifdef zox_octree_chunk_build_limits
        int chunks_built = 0;
    #endif
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 1);
    const ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 2);
    const RenderLod *renderLods = ecs_field(it, RenderLod, 3);
    const ChunkNeighbors *chunkNeighbors = ecs_field(it, ChunkNeighbors, 4);
    const VoxLink *voxLinks = ecs_field(it, VoxLink, 5);
    MeshIndicies *meshIndiciess = ecs_field(it, MeshIndicies, 6);
    MeshVertices *meshVerticess = ecs_field(it, MeshVertices, 7);
    MeshUVs *meshUVss = ecs_field(it, MeshUVs, 8);
    MeshColorRGBs *meshColorRGBss = ecs_field(it, MeshColorRGBs, 9);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 10);
    for (int i = 0; i < it->count; i++) {
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value == 0) continue;
        const RenderLod *renderLod = &renderLods[i];
        unsigned char lod = get_terrain_lod_from_camera_distance(renderLod->value);
        MeshDirty *meshDirty = &meshDirtys[i];
        MeshIndicies *meshIndicies = &meshIndiciess[i];
        MeshVertices *meshVertices = &meshVerticess[i];
        MeshColorRGBs *meshColorRGBs = &meshColorRGBss[i];
        MeshUVs *meshUVs = &meshUVss[i];
        if (lod == 255) { // hides mesh
            tri_count -= meshIndicies->length / 3;
            clear_memory_component(meshIndicies)
            clear_memory_component(meshVertices)
            clear_memory_component(meshColorRGBs)
            clear_memory_component(meshUVs)
            chunkDirty->value = 0;
            meshDirty->value = 1;
            continue;
        }
        const VoxLink *voxLink = &voxLinks[i];
        // waits for tilemap generation to finish
        const TilemapLink *tilemapLink = ecs_get(world, voxLink->value, TilemapLink);
        const TilemapUVs *tilemapUVs = ecs_get(world, tilemapLink->value, TilemapUVs);
        // waits for tilemap generation to be done
        if (tilemapUVs->value == NULL || tilemapUVs->length == 0) continue;
        const ChunkOctree *chunkOctree = &chunkOctrees[i];
        const ChunkNeighbors *chunkNeighbors2 = &chunkNeighbors[i];
        const ChunkOctree *chunk_left = chunkNeighbors2->value[0] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[0], ChunkOctree);
        const ChunkOctree *chunk_right = chunkNeighbors2->value[1] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[1], ChunkOctree);
        const ChunkOctree *chunk_down = chunkNeighbors2->value[2] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[2], ChunkOctree);
        const ChunkOctree *chunk_up = chunkNeighbors2->value[3] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[3], ChunkOctree);
        const ChunkOctree *chunk_back = chunkNeighbors2->value[4] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[4], ChunkOctree);
        const ChunkOctree *chunk_front = chunkNeighbors2->value[5] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[5], ChunkOctree);
        const ChunkOctree *neighbors[] =  { chunk_left, chunk_right, chunk_down, chunk_up, chunk_back, chunk_front };
        unsigned char chunk_left_max_distance = chunkNeighbors2->value[0] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[0], RenderLod)->value;
        unsigned char chunk_right_max_distance = chunkNeighbors2->value[1] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[1], RenderLod)->value;
        unsigned char chunk_down_max_distance = chunkNeighbors2->value[2] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[2], RenderLod)->value;
        unsigned char chunk_up_max_distance = chunkNeighbors2->value[3] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[3], RenderLod)->value;
        unsigned char chunk_back_max_distance = chunkNeighbors2->value[4] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[4], RenderLod)->value;
        unsigned char chunk_front_max_distance = chunkNeighbors2->value[5] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[5], RenderLod)->value;
        unsigned char *neighbor_lods = malloc(6);
        neighbor_lods[0] = get_terrain_lod_from_camera_distance(chunk_left_max_distance);
        neighbor_lods[1] = get_terrain_lod_from_camera_distance(chunk_right_max_distance);
        neighbor_lods[2] = get_terrain_lod_from_camera_distance(chunk_down_max_distance);
        neighbor_lods[3] = get_terrain_lod_from_camera_distance(chunk_up_max_distance);
        neighbor_lods[4] = get_terrain_lod_from_camera_distance(chunk_back_max_distance);
        neighbor_lods[5] = get_terrain_lod_from_camera_distance(chunk_front_max_distance);
        tri_count -= meshIndicies->length / 3;
        build_chunk_octree_mesh_uvs(chunkOctree, tilemapUVs, meshIndicies, meshVertices, meshUVs, meshColorRGBs, renderLod->value, lod, neighbors, neighbor_lods);
        tri_count += meshIndicies->length / 3;
        free(neighbor_lods);
        chunkDirty->value = 0;
        meshDirty->value = 1;
        #ifdef zox_octree_chunk_build_limits
            chunks_built++;
            if (chunks_built >= max_chunks_build_per_frame) break;
        #endif
        #ifdef zoxel_time_octree_chunk_builds_system
            did_do_timing()
        #endif
    }
    #ifdef zoxel_time_octree_chunk_builds_system
        end_timing_cutoff("    - octree_chunk_build_system", zoxel_time_octree_chunk_builds_system_cutoff)
    #endif
} zox_declare_system(ChunkOctreeBuildSystem)

// voxel_scale = 1.0f / 16.0f;

/*unsigned char get_division_amount(float voxel_scale) {
    if (voxel_scale == 1) return 1;
    unsigned char division_amount = 1;
    for (; voxel_scale > 1.0f; voxel_scale /= 2.0f) division_amount *= 2;
    return division_amount;
}*/

/*
for (offset2.x = - (voxel_scale / 2.0f) + 1; offset2.x <= (voxel_scale / 2.0f); offset2.x += 1.0f) {\
                for (offset2.z = - (voxel_scale / 2.0f) + 1; offset2.z <= (voxel_scale / 2.0f); offset2.z += 1.0f) {
             && voxel_scale == 2.0f
              && voxel_scale == 4.0f
*/