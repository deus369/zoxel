// #define disable_voxel_left
// #define disable_voxel_right
// #define disable_voxel_down
// #define disable_voxel_up
// #define disable_voxel_back
// #define disable_voxel_front

//! \todo Use a hashmap with bit map of side voxels, to generate voxel faces.
//      for example, top and bottom, would be 001100, and would have 8 vertexes and 12 indicies.

//! \todo combine vertices between voxel meshes.
//      For example, to up faces next to each other, will only have 6 vertices and now 8.

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
        float3 vertex_position = voxel_face_vertices[a]; // (float3) { cubeVertices[a + 0], cubeVertices[a + 1], cubeVertices[a + 2] };
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
                    #ifndef disable_voxel_left
                    zoxel_check_faces(left)
                    #endif
                    #ifndef disable_voxel_right
                    zoxel_check_faces(right)
                    #endif
                    #ifndef disable_voxel_down
                    zoxel_check_faces(down)
                    #endif
                    #ifndef disable_voxel_up
                    zoxel_check_faces(up)
                    #endif
                    #ifndef disable_voxel_back
                    zoxel_check_faces(back)
                    #endif
                    #ifndef disable_voxel_front
                    zoxel_check_faces(front)
                    #endif
                }
            }
        }
    }
    re_initialize_memory_component(meshIndicies, int, indicies_count);
    re_initialize_memory_component(meshVertices, float3, verticies_count);
    array_index = 0;
    for (local_position.x = 0; local_position.x < chunk_size.x; local_position.x++) {
        for (local_position.y = 0; local_position.y < chunk_size.y; local_position.y++) {
            for (local_position.z = 0; local_position.z < chunk_size.z; local_position.z++) {
                array_index = byte3_array_index(local_position, chunk_size);
                if (chunk->value[array_index] != 0) {
                    float3 vertex_position_offset = float3_from_byte3(local_position);
                    float3_multiply_float_p(&vertex_position_offset, voxel_scale);
                    // float3 vertex_position_offset = float3_multiply_float(float3_from_int3(local_position), voxel_scale);
                    #ifndef disable_voxel_left
                    zoxel_add_faces(left, 0)
                    #endif
                    #ifndef disable_voxel_right
                    zoxel_add_faces(right, 1)
                    #endif
                    #ifndef disable_voxel_down
                    zoxel_add_faces(down, 1)
                    #endif
                    #ifndef disable_voxel_up
                    zoxel_add_faces(up, 0)
                    #endif
                    #ifndef disable_voxel_back
                    zoxel_add_faces(back, 0)
                    #endif
                    #ifndef disable_voxel_front
                    zoxel_add_faces(front, 1)
                    #endif
                }
            }
        }
    }
}

void ChunkBuildSystem(ecs_iter_t *it) {
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL)) return;
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 1);
    const ChunkData *chunks = ecs_field(it, ChunkData, 2);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 3);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 4);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 5);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 6);
    for (int i = 0; i < it->count; i++) {
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value == 0) continue;
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 0) continue;
        chunkDirty->value = 0;
        meshDirty->value = 1;
        const ChunkData *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        build_chunk_mesh(chunk, chunkSize, meshIndicies2, meshVertices2);
        // zoxel_log("Building ChunkData Mesh [%lu] - [%i] [%i]\n", (long int) it->entities[i], meshIndicies2->length, meshVertices2->length);
    }
} zox_declare_system(ChunkBuildSystem)