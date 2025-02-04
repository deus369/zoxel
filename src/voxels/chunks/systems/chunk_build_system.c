/*
void add_voxel_face(MeshIndicies *meshIndicies2, MeshVertices *meshVertices2,
    float3 vertex_position_offset, float3 center_mesh_offset, float voxel_scale,
    int2 *start, int2 start2,
    const int voxel_face_indicies[], int voxel_face_indicies_length,
    const float3 voxel_face_vertices[], int voxel_face_vertices_length) {
    int indicies_offset = start2.y;
    for (int a = 0, b = start2.x; a < voxel_face_indicies_length; a++, b++) {
        meshIndicies2->value[b] = indicies_offset + voxel_face_indicies[a];
    }
    // add verts
    for (int a = 0, b = start2.y; a < voxel_face_vertices_length; a++, b = b + 1) {
        float3 vertex_position = voxel_face_vertices[a]; // (float3) { cube_vertices[a + 0], cube_vertices[a + 1], cube_vertices[a + 2] };
        vertex_position = float3_multiply_float(vertex_position, voxel_scale);          // scale vertex
        vertex_position = float3_add(vertex_position, vertex_position_offset);   // offset vertex by voxel position in chunk
        vertex_position = float3_add(vertex_position, center_mesh_offset);       // add total mesh offset
        meshVertices2->value[b] = vertex_position;
    }
    start->x += voxel_face_indicies_length;
    start->y += voxel_face_vertices_length;
}

void build_chunk_mesh(const ChunkData *chunk, const ChunkSize *chunkSize,
    MeshIndicies *meshIndicies, MeshVertices *meshVertices) {
    // go through and add a top face for each voxel position that is solid
    int array_index = 0;
    int indicies_count = 0;
    int verticies_count = 0;
    int2 start = { };
    float voxel_scale = overall_voxel_scale / ((float) chunkSize->value.x);
    byte3 chunk_size = (byte3) { chunkSize->value.x, chunkSize->value.y, chunkSize->value.z };
    byte3 local_position;
    for (local_position.x = 0; local_position.x < chunk_size.x; local_position.x++) {
        for (local_position.y = 0; local_position.y < chunk_size.y; local_position.y++) {
            for (local_position.z = 0; local_position.z < chunk_size.z; local_position.z++) {
                array_index = byte3_array_index(local_position, chunk_size);
                if (chunk->value[array_index] != 0) {
                    zoxel_check_faces(left)
                    zoxel_check_faces(right)
                    zoxel_check_faces(down)
                    zoxel_check_faces(up)
                    zoxel_check_faces(back)
                    zoxel_check_faces(front)
                }
            }
        }
    }
    resize_memory_component(MeshIndicies, meshIndicies, int, indicies_count);
    resize_memory_component(MeshVertices, meshVertices, float3, verticies_count);
    array_index = 0;
    for (local_position.x = 0; local_position.x < chunk_size.x; local_position.x++) {
        for (local_position.y = 0; local_position.y < chunk_size.y; local_position.y++) {
            for (local_position.z = 0; local_position.z < chunk_size.z; local_position.z++) {
                array_index = byte3_array_index(local_position, chunk_size);
                if (chunk->value[array_index] != 0) {
                    float3 vertex_position_offset = float3_from_byte3(local_position);
                    float3_multiply_float_p(&vertex_position_offset, voxel_scale);
                    zoxel_add_faces(left, 0)
                    zoxel_add_faces(right, 1)
                    zoxel_add_faces(down, 1)
                    zoxel_add_faces(up, 0)
                    zoxel_add_faces(back, 0)
                    zoxel_add_faces(front, 1)
                }
            }
        }
    }
}

void ChunkBuildSystem(ecs_iter_t *it) {
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL)) return;
    zox_field_in(ChunkData, chunkDatas, 2)
    zox_field_in(ChunkSize, chunkSizes, 3)
    zox_field_out(ChunkDirty, chunkDirtys, 1)
    zox_field_out(MeshIndicies, meshIndicies, 4)
    zox_field_out(MeshVertices, meshVertices, 5)
    zox_field_out(MeshDirty, meshDirtys, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value == chunk_dirty_state_none) continue;
        zox_field_o(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value == mesh_state_none) continue;
        zox_field_i(ChunkData, chunkDatas, chunkData)
        zox_field_i(ChunkSize, chunkSizes, chunkSize)
        zox_field_o(MeshIndicies, meshIndicies, meshIndicies2)
        zox_field_o(MeshVertices, meshVertices, meshVertices2)
        build_chunk_mesh(chunkData, chunkSize, meshIndicies2, meshVertices2);
        chunkDirty->value = chunk_dirty_state_none;
        meshDirty->value = mesh_state_trigger;
    }
} zox_declare_system(ChunkBuildSystem)
*/
