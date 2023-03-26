// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset
void add_voxel_face_uvs_d(int_array_d *indicies, float3_array_d* vertices, float2_array_d* uvs,
    float3 vertex_position_offset, float3 center_mesh_offset, float voxel_scale,
    const int* voxel_face_indicies, const float3 voxel_face_vertices[], const float2 voxel_face_uvs[]) {
    for (unsigned char a = 0; a < voxel_face_indicies_length; a++) {
        add_to_int_array_d(indicies, vertices->size + voxel_face_indicies[a]);
    }
    for (unsigned char a = 0; a < voxel_face_vertices_length; a++) {
        float3 vertex_position = voxel_face_vertices[a];
        float3_multiply_float_p(&vertex_position, voxel_scale);
        float3_add_float3_p(&vertex_position, vertex_position_offset);
        float3_add_float3_p(&vertex_position, center_mesh_offset);    
        add_to_float3_array_d(vertices, vertex_position);
        add_to_float2_array_d(uvs, voxel_face_uvs[a]);
    }
}

#define zoxel_octree_build_face_d(direction, is_positive) \
    zoxel_octree_check(direction) {\
        add_voxel_face_uvs_d(indicies, vertices, uvs, vertex_position_offset, center_mesh_offset,\
        voxel_scale, get_voxel_indices(is_positive), voxel_face_vertices##_##direction, voxel_face_uvs);\
    }

void build_octree_chunk_d(const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree, const ChunkOctree *neighbors[],
    unsigned char neighbors_max_depths[], int_array_d *indicies, float3_array_d* vertices, float2_array_d* uvs,
    unsigned char depth, unsigned char max_depth, int3 octree_position, int3 node_position, float scale) {
    if (depth >= max_depth || chunk_octree->nodes == NULL) {
        if (chunk_octree->value != 0) {
            float voxel_scale = scale * (overall_voxel_scale / ((float) octree_node_size));
            float3 center_mesh_offset = (float3) { - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };
            float3 vertex_position_offset = float3_from_int3(octree_position);
            float3_multiply_float_p(&vertex_position_offset, voxel_scale);
            zoxel_octree_build_face_d(left, 0)
            zoxel_octree_build_face_d(right, 1)
            zoxel_octree_build_face_d(down, 1)
            zoxel_octree_build_face_d(up, 0)
            zoxel_octree_build_face_d(back, 0)
            zoxel_octree_build_face_d(front, 1)
        }
    } else {
        depth++;
        scale *= 0.5f;
        int3_multiply_int_p(&octree_position, 2);
        int3 local_position;
        for (local_position.x = 0; local_position.x < octree_node_size; local_position.x++) {
            for (local_position.y = 0; local_position.y < octree_node_size; local_position.y++) {
                for (local_position.z = 0; local_position.z < octree_node_size; local_position.z++) {
                    int array_index = int3_array_index(local_position, octree_node_size3);
                    ChunkOctree node = chunk_octree->nodes[array_index];
                    if (node.value == 0) {
                        continue;
                    }
                    int3 child_octree_position = int3_add(octree_position, local_position);
                    build_octree_chunk_d(root_node, chunk_octree, &chunk_octree->nodes[array_index],
                        neighbors, neighbors_max_depths, indicies, vertices, uvs,
                        depth, max_depth, child_octree_position, local_position, scale);
                }
            }
        }
    }
}

void build_octree_chunk_mesh_uvs(const ChunkOctree *chunk_octree, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    unsigned char chunk_division, const ChunkOctree *neighbors[], unsigned char neighbors_max_depths[]) {
    // try using a list of mesh data and then converting to an array instead and comparing speeds
    int2 mesh_count = { 0, 0 };
    unsigned char max_depth = get_max_depth_from_division(chunk_division);
    #ifdef zoxel_voxels_dynamic_array
        int_array_d* indicies = create_int_array_d();
        float3_array_d* vertices = create_float3_array_d();
        float2_array_d* uvs = create_float2_array_d();
        build_octree_chunk_d(chunk_octree, NULL, chunk_octree, neighbors, neighbors_max_depths,
            indicies, vertices, uvs, 0, max_depth, int3_zero, int3_zero, 2.0f);
        if (meshIndicies->length != 0) {
            free(meshIndicies->value);
        }
        if (meshVertices->length != 0) {
            free(meshVertices->value);
        }
        if (meshUVs->length != 0) {
            free(meshUVs->value);
        }
        meshIndicies->length = indicies->size;
        meshVertices->length = vertices->size;
        meshUVs->length = uvs->size;
        meshIndicies->value = finalize_int_array_d(indicies);
        meshVertices->value = finalize_float3_array_d(vertices);
        meshUVs->value = finalize_float2_array_d(uvs);
    #else
        int2 *start = &((int2) { 0, 0 });
        count_octree_chunk(chunk_octree, NULL, chunk_octree, neighbors, neighbors_max_depths, meshIndicies, meshVertices, meshUVs, &mesh_count, 0, max_depth, int3_zero, int3_zero);
        re_initialize_memory_component(meshIndicies, int, mesh_count.x);
        re_initialize_memory_component(meshVertices, float3, mesh_count.y);
        re_initialize_memory_component(meshUVs, float2, mesh_count.y);
        build_octree_chunk(chunk_octree, NULL, chunk_octree, neighbors, neighbors_max_depths,
            meshIndicies, meshVertices, meshUVs, start, 0, max_depth, int3_zero, int3_zero, 2.0f);
    #endif
}

void OctreeChunkBuildSystem(ecs_iter_t *it) {
    if (disable_chunk_systems) return;
    if (!ecs_query_changed(it->ctx, NULL)) {
        return;
    }
    #ifdef zoxel_time_octree_chunk_builds_system
        begin_timing()
    #endif
    const ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 1);
    const ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 2);
    const ChunkDivision *chunkDivisions = ecs_field(it, ChunkDivision, 3);
    const ChunkNeighbors *chunkNeighbors = ecs_field(it, ChunkNeighbors, 4);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 5);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 6);
    MeshUVs *meshUVs = ecs_field(it, MeshUVs, 7);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 8);
    for (int i = 0; i < it->count; i++) {
        const ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value == 0) {
            continue;
        }
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 0) {
            continue;
        }
        meshDirty->value = 1;
        const ChunkOctree *chunkOctree = &chunkOctrees[i];
        const ChunkDivision *chunkDivision = &chunkDivisions[i];
        const ChunkNeighbors *chunkNeighbors2 = &chunkNeighbors[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        MeshUVs *meshUVs2 = &meshUVs[i];
        if (meshIndicies2->length != 0) {
            tri_count -= meshIndicies2->length / 3;
        }
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
        unsigned char neighbors_max_depths[] = {
            get_max_depth_from_division(chunk_left_max_distance), get_max_depth_from_division(chunk_right_max_distance),
            get_max_depth_from_division(chunk_down_max_distance), get_max_depth_from_division(chunk_up_max_distance),
            get_max_depth_from_division(chunk_back_max_distance), get_max_depth_from_division(chunk_front_max_distance)
        };
        build_octree_chunk_mesh_uvs(chunkOctree, meshIndicies2, meshVertices2, meshUVs2, chunkDivision->value, neighbors, neighbors_max_depths);
        #ifdef zoxel_time_octree_chunk_builds_system
            did_do_timing()
        #endif
    }
    #ifdef zoxel_time_octree_chunk_builds_system
        end_timing("    - octree_chunk_build_system")
    #endif
}
zoxel_declare_system(OctreeChunkBuildSystem)