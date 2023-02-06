//! Add vertices and uvs to the chunk one.
void add_voxel_face_uvs(MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    float3 vertex_position_offset, float3 center_mesh_offset, float voxel_scale,
    int2 *mesh_start,
    const int voxel_face_indicies[], int voxel_face_indicies_length,
    const float3 voxel_face_vertices[], int voxel_face_vertices_length,
    const float2 voxel_face_uvs[])
{
    for (int a = 0, b = mesh_start->x; a < voxel_face_indicies_length; a++, b++)
    {
        // printf("b [%i]\n", b);
        meshIndicies->value[b] = mesh_start->y + voxel_face_indicies[a];
    }
    // add verts
    for (int a = 0, b = mesh_start->y, c = mesh_start->y; a < voxel_face_vertices_length; a++, b++, c++)
    {
        float3 vertex_position = voxel_face_vertices[a]; // (float3) { cubeVertices[a + 0], cubeVertices[a + 1], cubeVertices[a + 2] };
        vertex_position = float3_multiply_float(vertex_position, voxel_scale);          // scale vertex
        vertex_position = float3_add(vertex_position, vertex_position_offset);   // offset vertex by voxel position in chunk
        vertex_position = float3_add(vertex_position, center_mesh_offset);       // add total mesh offset
        meshVertices->value[b] = vertex_position;
        meshUVs->value[c] = voxel_face_uvs[a];
    }
    mesh_start->x += voxel_face_indicies_length;
    mesh_start->y += voxel_face_vertices_length;
}

void build_chunk_mesh_uvs(const ChunkData *chunk, const ChunkSize *chunkSize,
    MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    const ChunkData *chunk_left, const ChunkData *chunk_right,
    const ChunkData *chunk_back, const ChunkData *chunk_front)
{
    int2 *mesh_count = &((int2){ 0, 0 });
    int2 *start = &((int2) { 0, 0 });
    // int indicies_count = 0;
    // int verticies_count = 0;
    // int uvs_count = 0;
    int3 local_position;
    float voxel_scale = overall_voxel_scale / ((float) chunkSize->value.x);
    float3 center_mesh_offset = (float3) { - overall_voxel_scale / 2.0f,
        - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };
    //! Precount our index and vertex array lengths.
    for (local_position.x = 0; local_position.x < chunkSize->value.x; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < chunkSize->value.y; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < chunkSize->value.z; local_position.z++)
            {
                int array_index = int3_array_index(local_position, chunkSize->value);
                if (chunk->value[array_index] != 0)
                {
                    // add faces - based on neighbor voxels.
                    #ifndef disable_voxel_left
                    zoxel_check_faces_with_uvs(left)
                    #endif
                    #ifndef disable_voxel_right
                    zoxel_check_faces_with_uvs(right)
                    #endif
                    #ifndef disable_voxel_down
                    zoxel_check_faces_no_chunk(down)
                    #endif
                    #ifndef disable_voxel_up
                    zoxel_check_faces_no_chunk(up)
                    #endif
                    #ifndef disable_voxel_back
                    zoxel_check_faces_with_uvs(back)
                    #endif
                    #ifndef disable_voxel_front
                    zoxel_check_faces_with_uvs(front)
                    #endif
                }
            }
        }
    }
    //! Create our index and vertex arrays
    re_initialize_memory_component(meshIndicies, int, mesh_count->x);
    re_initialize_memory_component(meshVertices, float3, mesh_count->y);
    re_initialize_memory_component(meshUVs, float2, mesh_count->y);
    for (local_position.x = 0; local_position.x < chunkSize->value.x; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < chunkSize->value.y; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < chunkSize->value.z; local_position.z++)
            {
                int array_index = int3_array_index(local_position, chunkSize->value);
                if (chunk->value[array_index] == 0)
                {
                    continue;
                }
                float3 vertex_position_offset = float3_multiply_float(float3_from_int3(local_position), voxel_scale);
                #ifndef disable_voxel_left
                zoxel_add_faces_with_uvs(left, 0)
                #endif
                #ifndef disable_voxel_right
                zoxel_add_faces_with_uvs(right, 1)
                #endif
                #ifndef disable_voxel_down
                zoxel_add_faces_no_chunk(down, 1)
                #endif
                #ifndef disable_voxel_up
                zoxel_add_faces_no_chunk(up, 0)
                #endif
                #ifndef disable_voxel_back
                zoxel_add_faces_with_uvs(back, 0)
                #endif
                #ifndef disable_voxel_front
                zoxel_add_faces_with_uvs(front, 1)
                #endif
            }
        }
    }
}

//! Builds a mesh data from the chunk!
void ChunkUVsBuildSystem(ecs_iter_t *it)
{
    if (disable_chunk_systems) return;
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    // printf("[ChunkBuildSystem] GenerateChunk was changed.\n");
    const ChunkDirty *entityDirtys = ecs_field(it, ChunkDirty, 1);
    const ChunkData *chunks = ecs_field(it, ChunkData, 2);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 3);
    const ChunkNeighbors *chunkNeighbors = ecs_field(it, ChunkNeighbors, 4);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 5);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 6);
    MeshUVs *meshUVs = ecs_field(it, MeshUVs, 7);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 8);
    for (int i = 0; i < it->count; i++)
    {
        const ChunkDirty *chunkDirty = &entityDirtys[i];
        if (chunkDirty->value == 0)
        {
            continue;
        }
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 0)
        {
            continue;
        }
        meshDirty->value = 1;
        const ChunkData *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        const ChunkNeighbors *chunkNeighbors2 = &chunkNeighbors[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        MeshUVs *meshUVs2 = &meshUVs[i];
        const ChunkData *chunk_left = chunkNeighbors2->value[0] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[0], ChunkData);
        const ChunkData *chunk_right = chunkNeighbors2->value[1] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[1], ChunkData);
        const ChunkData *chunk_back = chunkNeighbors2->value[2] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[2], ChunkData);
        const ChunkData *chunk_front = chunkNeighbors2->value[3] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[3], ChunkData);
        build_chunk_mesh_uvs(chunk, chunkSize, meshIndicies2, meshVertices2, meshUVs2,
            chunk_left, chunk_right, chunk_back, chunk_front);
        // printf("Building ChunkData UVs Mesh [%lu]\n", (long int) it->entities[i]);
    }
}
zoxel_declare_system(ChunkUVsBuildSystem)