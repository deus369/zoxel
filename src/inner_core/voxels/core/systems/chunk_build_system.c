// #define disable_voxel_left
// #define disable_voxel_right
// #define disable_voxel_down
// #define disable_voxel_up
// #define disable_voxel_back
// #define disable_voxel_front

void add_voxel_face(MeshIndicies *meshIndicies2, MeshVertices *meshVertices2,
    float3 vertex_position_offset, float3 center_mesh_offset, float voxel_scale,
    int2 *start, int2 start2,
    const int voxel_face_indicies[], int voxel_face_indicies_length,
    const float3 voxel_face_vertices[], int voxel_face_vertices_length)
{
    int indicies_offset = start2.y;
    for (int a = 0, b = start2.x; a < voxel_face_indicies_length; a++, b++)
    {
        meshIndicies2->value[b] = indicies_offset + voxel_face_indicies[a];
    }
    // add verts
    for (int a = 0, b = start2.y; a < voxel_face_vertices_length; a++, b = b + 1)
    {
        float3 vertex_position = voxel_face_vertices[a]; // (float3) { cubeVertices[a + 0], cubeVertices[a + 1], cubeVertices[a + 2] };
        vertex_position = float3_multiply_float(vertex_position, voxel_scale);          // scale vertex
        vertex_position = float3_add(vertex_position, vertex_position_offset);   // offset vertex by voxel position in chunk
        vertex_position = float3_add(vertex_position, center_mesh_offset);       // add total mesh offset
        meshVertices2->value[b] = vertex_position;
    }
    start->x += voxel_face_indicies_length;
    start->y += voxel_face_vertices_length;
}

void build_chunk_mesh(const Chunk *chunk, const ChunkSize *chunkSize,
    MeshIndicies *meshIndicies, MeshVertices *meshVertices)
{
    // go through and add a top face for each voxel position that is solid
    int array_index = 0;
    int indicies_count = 0;
    int verticies_count = 0;
    int3 local_position;
    int2 start = { };
    float voxel_scale = overall_voxel_scale / ((float) chunkSize->value.x); // 16.0f;
    float3 center_mesh_offset = (float3) { - overall_voxel_scale / 2.0f,
        - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };
    // precount our face data for initialization
    for (local_position.x = 0; local_position.x < chunkSize->value.x; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < chunkSize->value.y; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < chunkSize->value.z; local_position.z++)
            {
                array_index = int3_array_index(local_position, chunkSize->value);
                if (chunk->value[array_index] != 0)
                {
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
    for (local_position.x = 0; local_position.x < chunkSize->value.x; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < chunkSize->value.y; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < chunkSize->value.z; local_position.z++)
            {
                array_index = int3_array_index(local_position, chunkSize->value);
                if (chunk->value[array_index] != 0)
                {
                    float3 vertex_position_offset = float3_multiply_float(float3_from_int3(local_position), voxel_scale);
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

//! Builds a mesh data from the chunk!
void ChunkBuildSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    // printf("[ChunkBuildSystem] GenerateChunk was changed.\n");
    const ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 1);
    const Chunk *chunks = ecs_field(it, Chunk, 2);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 3);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 4);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 5);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 6);
    for (int i = 0; i < it->count; i++)
    {
        const ChunkDirty *chunkDirty = &chunkDirtys[i];
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
        const Chunk *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        build_chunk_mesh(chunk, chunkSize, meshIndicies2, meshVertices2);
        // printf("Building Chunk Mesh [%lu] - [%i] [%i]\n",
        //    (long int) it->entities[i], meshIndicies2->length, meshVertices2->length);
    }
}
ECS_SYSTEM_DECLARE(ChunkBuildSystem);

//! \todo Use a hashmap with bit map of side voxels, to generate voxel faces.
//      for example, top and bottom, would be 001100, and would have 8 vertexes and 12 indicies.

//! \todo combine vertices between voxel meshes.
//      For example, to up faces next to each other, will only have 6 vertices and now 8.


// invalid free?
// printf("Rebuilding Chunk Mesh: %i - %i\n", meshIndicies2->length, meshVertices2->length);
/*printf("1 - MeshIndicies: %i\n", meshIndicies2->length);
set_mesh_indicies(meshIndicies2, cubeIndicies, 36);
set_mesh_vertices(meshVertices2, cubeVertices, 24);*/
// printf("Rebuilding Chunk Mesh with faces: [%i]\n", solid_voxels_count);

/*if (k == 0 && l == 0)
{
    printf("Voxel [%i] - [%ix%ix%i]:\n", solid_voxels_count, j, k, l);
    printf("    vertex_position_offset [%fx%fx%f]\n",  vertex_position_offset.x, vertex_position_offset.y, vertex_position_offset.z);
    printf("    vertices_start [%i]\n", vertices_start);
}*/