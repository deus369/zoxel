/*void build_chunk_mesh_uvs(const ChunkData *chunk, const ChunkSize *chunkSize,
    MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    const ChunkData *chunk_left, const ChunkData *chunk_right,
    const ChunkData *chunk_back, const ChunkData *chunk_front) {
    int2 *mesh_count = &((int2){ 0, 0 });
    int2 *start = &((int2) { 0, 0 });
    float voxel_scale = overall_voxel_scale / ((float) chunkSize->value.x);
    // float3 center_mesh_offset = (float3) { - overall_voxel_scale / 2.0f,
    //    - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };
    //! Precount our index and vertex array lengths.
    byte3 chunk_size = (byte3) { chunkSize->value.x, chunkSize->value.y, chunkSize->value.z };
    byte3 local_position;
    for (local_position.x = 0; local_position.x < chunk_size.x; local_position.x++) {
        for (local_position.y = 0; local_position.y < chunk_size.y; local_position.y++) {
            for (local_position.z = 0; local_position.z < chunk_size.z; local_position.z++) {
                int array_index = byte3_array_index(local_position, chunk_size);
                if (chunk->value[array_index] != 0) {
                    zoxel_check_faces_with_uvs(left)
                    zoxel_check_faces_with_uvs(right)
                    zoxel_check_faces_no_chunk(down)
                    zoxel_check_faces_no_chunk(up)
                    zoxel_check_faces_with_uvs(back)
                    zoxel_check_faces_with_uvs(front)
                }
            }
        }
    }
    //! Create our index and vertex arrays
    resize_memory_component(MeshIndicies, meshIndicies, int, mesh_count->x);
    resize_memory_component(MeshVertices, meshVertices, float3, mesh_count->y);
    resize_memory_component(MeshUVs, meshUVs, float2, mesh_count->y);
    for (local_position.x = 0; local_position.x < chunk_size.x; local_position.x++) {
        for (local_position.y = 0; local_position.y < chunk_size.y; local_position.y++) {
            for (local_position.z = 0; local_position.z < chunk_size.z; local_position.z++) {
                int array_index = byte3_array_index(local_position, chunk_size);
                if (chunk->value[array_index] == 0) continue;
                float3 vertex_position_offset = float3_from_byte3(local_position);
                float3_multiply_float_p(&vertex_position_offset, voxel_scale);
                zoxel_add_faces_with_uvs(left, 0)
                zoxel_add_faces_with_uvs(right, 1)
                zoxel_add_faces_no_chunk(down, 1)
                zoxel_add_faces_no_chunk(up, 0)
                zoxel_add_faces_with_uvs(back, 0)
                zoxel_add_faces_with_uvs(front, 1)
            }
        }
    }
}

void ChunkUVsBuildSystem(ecs_iter_t *it) {
    zox_change_check()
    zox_field_out(ChunkDirty, chunkDirtys, 1)
    const ChunkData *chunks = ecs_field(it, ChunkData, 2);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 3);
    const ChunkNeighbors *chunkNeighbors = ecs_field(it, ChunkNeighbors, 4);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 5);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 6);
    MeshUVs *meshUVs = ecs_field(it, MeshUVs, 7);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 8);
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value == chunk_dirty_state_none) continue;
        MeshDirty *meshDirty = &meshDirtys[i];
        // if (meshDirty->value != 0) continue;
        const ChunkData *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        const ChunkNeighbors *chunkNeighbors2 = &chunkNeighbors[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        MeshUVs *meshUVs2 = &meshUVs[i];
        const ChunkData *chunk_left = chunkNeighbors2->value[0] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[0], ChunkData);
        const ChunkData *chunk_right = chunkNeighbors2->value[1] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[1], ChunkData);
        const ChunkData *chunk_back = chunkNeighbors2->value[2] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[2], ChunkData);
        const ChunkData *chunk_front = chunkNeighbors2->value[3] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[3], ChunkData);
        build_chunk_mesh_uvs(chunk, chunkSize, meshIndicies2, meshVertices2, meshUVs2, chunk_left, chunk_right, chunk_back, chunk_front);
        chunkDirty->value = chunk_dirty_state_none;
        meshDirty->value = mesh_state_updated;
    }
} zox_declare_system(ChunkUVsBuildSystem)
*/
