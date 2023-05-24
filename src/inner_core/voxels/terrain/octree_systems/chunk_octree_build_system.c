// add uv splitting here based on voxel uvs - voxel_face_uvs based on voxel
// for now lets try

#define add_voxel_face_uvs_indicies(index)\
    indicies->data[indicies->size + index] = vertices->size + voxel_face_indicies[index];

#define add_voxel_face_uvs_vertices(index) {\
    float3 vertex_position = voxel_face_vertices[index];\
    float3_multiply_float_p(&vertex_position, voxel_scale);\
    float3_add_float3_p(&vertex_position, vertex_position_offset);\
    vertices->data[vertices->size + index] = vertex_position;\
}

#define add_voxel_face_uvs_uvs(index)\
    uvs->data[uvs->size + index] = voxel_face_uvs[index];

// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset
void add_voxel_face_uvs_d(int_array_d *indicies, float3_array_d* vertices, float2_array_d* uvs, color_rgb_array_d* color_rgbs,
    float3 vertex_position_offset, unsigned char voxel, float voxel_scale,
    const int* voxel_face_indicies, const float3 voxel_face_vertices[], const float2 voxel_face_uvs[], unsigned char direction) {
    expand_capacity_int_array_d(indicies, voxel_face_indicies_length);
        add_voxel_face_uvs_indicies(0)
        add_voxel_face_uvs_indicies(1)
        add_voxel_face_uvs_indicies(2)
        add_voxel_face_uvs_indicies(3)
        add_voxel_face_uvs_indicies(4)
        add_voxel_face_uvs_indicies(5)
    indicies->size += voxel_face_indicies_length;
    expand_capacity_float3_array_d(vertices, voxel_face_vertices_length);
        add_voxel_face_uvs_vertices(0)
        add_voxel_face_uvs_vertices(1)
        add_voxel_face_uvs_vertices(2)
        add_voxel_face_uvs_vertices(3)
    vertices->size += voxel_face_vertices_length;
    expand_capacity_float2_array_d(uvs, voxel_face_vertices_length);
        add_voxel_face_uvs_uvs(0)
        add_voxel_face_uvs_uvs(1)
        add_voxel_face_uvs_uvs(2)
        add_voxel_face_uvs_uvs(3)
    uvs->size += voxel_face_vertices_length;
    for (int a = 0; a < voxel_face_vertices_length; a++) {
        color_rgb vertex_color = color_rgb_white;
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

#define zoxel_octree_build_face_d(direction_name, is_positive, voxel_uvs)\
if (!is_adjacent_all_solid(direction##_##direction_name, root_node, parent_node, neighbors,\
    octree_position, node_index, node_position, depth, lod, neighbor_lods, edge_voxel)) {\
    add_voxel_face_uvs_d(indicies, vertices, uvs, color_rgbs, vertex_position_offset, voxel,\
        voxel_scale, get_voxel_indices(is_positive), voxel_face_vertices##_##direction_name,\
        voxel_uvs, direction##_##direction_name);\
}

#define build_octree_chunk_child_node(i)\
if (chunk_octree->nodes[i].value != 0) {\
    build_octree_chunk_d(root_node, chunk_octree, &chunk_octree->nodes[i], neighbors, neighbor_lods,\
        indicies, vertices, uvs, color_rgbs, lod, depth, int3_add(octree_position, octree_positions[i]), i);\
}

void build_octree_chunk_d(const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree,
    const ChunkOctree *neighbors[], const unsigned char *neighbor_lods,
    int_array_d *indicies, float3_array_d* vertices, float2_array_d* uvs, color_rgb_array_d* color_rgbs,
    const unsigned char lod, unsigned char depth, int3 octree_position, const unsigned char node_index) {
    if (depth >= lod || chunk_octree->nodes == NULL) {
        if (chunk_octree->value != 0) {
            float voxel_scale = octree_scales3[depth];
            float3 vertex_position_offset = { octree_position.x * voxel_scale, octree_position.y * voxel_scale, octree_position.z * voxel_scale }; //float3_from_int3(octree_position);
            byte3 node_position = octree_positions_b[node_index];
            unsigned char voxel = chunk_octree->value;
            unsigned char edge_voxel;
            #ifdef voxels_hide_terrain_edge
                edge_voxel = 1;
            #else
                edge_voxel = 0;
            #endif
            if (voxel == 1) {
                zoxel_octree_build_face_d(left, 0, voxel_uvs_0)
                zoxel_octree_build_face_d(right, 1, voxel_uvs_0)
                zoxel_octree_build_face_d(down, 1, voxel_uvs_0)
                zoxel_octree_build_face_d(up, 0, voxel_uvs_0)
                zoxel_octree_build_face_d(back, 0, voxel_uvs_0)
                zoxel_octree_build_face_d(front, 1, voxel_uvs_0)
            } else { // if (voxel == 2) {
                zoxel_octree_build_face_d(left, 0, voxel_uvs_1)
                zoxel_octree_build_face_d(right, 1, voxel_uvs_1)
                zoxel_octree_build_face_d(down, 1, voxel_uvs_1)
                zoxel_octree_build_face_d(up, 0, voxel_uvs_1)
                zoxel_octree_build_face_d(back, 0, voxel_uvs_1)
                zoxel_octree_build_face_d(front, 1, voxel_uvs_1)
            }
        }
    } else {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        build_octree_chunk_child_node(0)
        build_octree_chunk_child_node(1)
        build_octree_chunk_child_node(2)
        build_octree_chunk_child_node(3)
        build_octree_chunk_child_node(4)
        build_octree_chunk_child_node(5)
        build_octree_chunk_child_node(6)
        build_octree_chunk_child_node(7)
    }
}

void build_chunk_octree_mesh_uvs(const ChunkOctree *chunk_octree, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs, MeshColorRGBs *meshColorRGBs,
    unsigned char lod, const ChunkOctree *neighbors[], unsigned char *neighbor_lods) {
    #ifdef zoxel_voxels_dynamic_array
        int_array_d* indicies = create_int_array_d();
        float3_array_d* vertices = create_float3_array_d();
        float2_array_d* uvs = create_float2_array_d();
        color_rgb_array_d* color_rgbs = create_color_rgb_array_d();
        build_octree_chunk_d(chunk_octree, NULL, chunk_octree, neighbors, neighbor_lods, indicies, vertices, uvs, color_rgbs, lod, 0, int3_zero, 0);
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
    int chunks_built = 0;
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 1);
    const ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 2);
    const RenderLod *renderLods = ecs_field(it, RenderLod, 3);
    const ChunkNeighbors *chunkNeighbors = ecs_field(it, ChunkNeighbors, 4);
    MeshIndicies *meshIndiciess = ecs_field(it, MeshIndicies, 5);
    MeshVertices *meshVerticess = ecs_field(it, MeshVertices, 6);
    MeshUVs *meshUVss = ecs_field(it, MeshUVs, 7);
    MeshColorRGBs *meshColorRGBss = ecs_field(it, MeshColorRGBs, 8);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 9);
    for (int i = 0; i < it->count; i++) {
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value != 1) continue;
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
        const ChunkOctree *chunkOctree = &chunkOctrees[i];
        const ChunkNeighbors *chunkNeighbors2 = &chunkNeighbors[i];
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
            0 : ecs_get(it->world, chunkNeighbors2->value[0], RenderLod)->value;
        unsigned char chunk_right_max_distance = chunkNeighbors2->value[1] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[1], RenderLod)->value;
        unsigned char chunk_down_max_distance = chunkNeighbors2->value[2] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[2], RenderLod)->value;
        unsigned char chunk_up_max_distance = chunkNeighbors2->value[3] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[3], RenderLod)->value;
        unsigned char chunk_back_max_distance = chunkNeighbors2->value[4] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[4], RenderLod)->value;
        unsigned char chunk_front_max_distance = chunkNeighbors2->value[5] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[5], RenderLod)->value;
        unsigned char *neighbor_lods = malloc(6);
        neighbor_lods[0] = get_terrain_lod_from_camera_distance(chunk_left_max_distance);
        neighbor_lods[1] = get_terrain_lod_from_camera_distance(chunk_right_max_distance);
        neighbor_lods[2] = get_terrain_lod_from_camera_distance(chunk_down_max_distance);
        neighbor_lods[3] = get_terrain_lod_from_camera_distance(chunk_up_max_distance);
        neighbor_lods[4] = get_terrain_lod_from_camera_distance(chunk_back_max_distance);
        neighbor_lods[5] = get_terrain_lod_from_camera_distance(chunk_front_max_distance);
        tri_count -= meshIndicies->length / 3;
        build_chunk_octree_mesh_uvs(chunkOctree, meshIndicies, meshVertices, meshUVs, meshColorRGBs, lod, neighbors, neighbor_lods);
        tri_count += meshIndicies->length / 3;
        free(neighbor_lods);
        chunkDirty->value = 0;
        meshDirty->value = 1;
        chunks_built++;
        if (chunks_built >= max_chunks_build_per_frame) break;
        #ifdef zoxel_time_octree_chunk_builds_system
            did_do_timing()
        #endif
    }
    #ifdef zoxel_time_octree_chunk_builds_system
        end_timing_cutoff("    - octree_chunk_build_system", zoxel_time_octree_chunk_builds_system_cutoff)
    #endif
}
zox_declare_system(ChunkOctreeBuildSystem)