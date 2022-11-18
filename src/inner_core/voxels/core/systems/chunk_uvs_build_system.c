void add_voxel_face_uvs(MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    float3 vertex_position_offset, float3 center_mesh_offset, float voxel_scale,
    int2 *start, int2 start2,
    const int voxel_face_indicies[], int voxel_face_indicies_length,
    const float3 voxel_face_vertices[], int voxel_face_vertices_length,
    const float2 voxel_face_uvs[])
{
    int indicies_offset = start2.y / 3;
    for (int a = 0, b = start2.x; a < voxel_face_indicies_length; a++, b++)
    {
        meshIndicies->value[b] = indicies_offset + voxel_face_indicies[a];
    }
    // add verts
    for (int a = 0, b = start2.y, c = 0; a < voxel_face_vertices_length; a++, b = b + 3, c = c + 2)
    {
        float3 vertex_position = voxel_face_vertices[a]; // (float3) { cubeVertices[a + 0], cubeVertices[a + 1], cubeVertices[a + 2] };
        vertex_position = float3_multiply_float(vertex_position, voxel_scale);          // scale vertex
        vertex_position = float3_add(vertex_position, vertex_position_offset);   // offset vertex by voxel position in chunk
        vertex_position = float3_add(vertex_position, center_mesh_offset);       // add total mesh offset
        meshVertices->value[b + 0] = vertex_position.x;
        meshVertices->value[b + 1] = vertex_position.y;
        meshVertices->value[b + 2] = vertex_position.z;
        float2 uv = voxel_face_uvs[a];
        meshUVs->value[c] = uv.x;
        meshUVs->value[c + 1] = uv.y;
    }
    start->x += voxel_face_indicies_up_length;
    start->y += voxel_face_vertices_length * 3;
}

void build_chunk_mesh_uvs(const Chunk *chunk, const ChunkSize *chunkSize,
    MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs)
{
    // int array_index = 0;
    int indicies_count = 0;
    int verticies_count = 0;
    int uvs_count = 0;
    int3 local_position;
    int2 start = { };
    float voxel_scale = overall_voxel_scale / ((float) chunkSize->value.x); // 16.0f;
    float3 center_mesh_offset = (float3) {
        - overall_voxel_scale / 2.0f,
        - overall_voxel_scale / 2.0f,
        - overall_voxel_scale / 2.0f };
    // precount our face data for initialization
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
                    /*#ifndef disable_voxel_left
                        // left
                        unsigned char voxel_left = local_position.x == 0 ?
                            0 : chunk->value[int3_array_index(int3_left(local_position), chunkSize->value)];
                        if (voxel_left == 0)
                        {
                            indicies_count += voxel_face_indicies_left_length;
                            verticies_count += voxel_face_vertices_left_length * 3;
                        }
                    #endif
                    #ifndef disable_voxel_right
                        // right
                        unsigned char voxel_right = local_position.x == chunkSize->value.x - 1 ?
                            0 : chunk->value[int3_array_index(int3_right(local_position), chunkSize->value)];
                        if (voxel_right == 0)
                        {
                            indicies_count += voxel_face_indicies_right_length;
                            verticies_count += voxel_face_vertices_right_length * 3;
                        }
                    #endif
                    #ifndef disable_voxel_down
                        // down
                        unsigned char voxel_down = local_position.y == 0 ?
                            0 : chunk->value[int3_array_index(int3_down(local_position), chunkSize->value)];
                        if (voxel_down == 0)
                        {
                            indicies_count += voxel_face_indicies_down_length;
                            verticies_count += voxel_face_vertices_down_length * 3;
                        }
                    #endif*/
                    #ifndef disable_voxel_up
                        // up
                        unsigned char voxel_up = local_position.y == chunkSize->value.y - 1 ?
                            0 : chunk->value[int3_array_index(int3_up(local_position), chunkSize->value)];
                        if (voxel_up == 0)
                        {
                            indicies_count += voxel_face_indicies_up_length;
                            verticies_count += voxel_face_vertices_up_length * 3;
                            uvs_count += voxel_face_vertices_up_length * 2;
                        }
                    #endif
                    /*#ifndef disable_voxel_back
                        // back
                        unsigned char voxel_back = local_position.z == 0 ?
                            0 : chunk->value[int3_array_index(int3_back(local_position), chunkSize->value)];
                        if (voxel_back == 0)
                        {
                            indicies_count += voxel_face_indicies_up_length;
                            verticies_count += voxel_face_vertices_up_length * 3;
                        }
                    #endif
                    #ifndef disable_voxel_front
                        // front
                        unsigned char voxel_front = local_position.z == chunkSize->value.z - 1 ?
                            0 : chunk->value[int3_array_index(int3_front(local_position), chunkSize->value)];
                        if (voxel_front == 0)
                        {
                            indicies_count += voxel_face_indicies_up_length;
                            verticies_count += voxel_face_vertices_up_length * 3;
                        }
                    #endif*/
                }
                // array_index++;
            }
        }
    }
    re_initialize_memory_component(meshIndicies, int, indicies_count);
    re_initialize_memory_component(meshVertices, float, verticies_count);
    re_initialize_memory_component(meshUVs, float, uvs_count);
    // array_index = 0;
    for (local_position.x = 0; local_position.x < chunkSize->value.x; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < chunkSize->value.y; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < chunkSize->value.z; local_position.z++)
            {
                int array_index = int3_array_index(local_position, chunkSize->value);
                if (chunk->value[array_index] != 0)
                {
                    float3 vertex_position_offset = float3_multiply_float(
                        float3_from_int3(local_position), voxel_scale);
                    /*#ifndef disable_voxel_left
                        unsigned char voxel_left = local_position.x == 0 ?
                            0 : chunk->value[int3_array_index(int3_left(local_position), chunkSize->value)];
                        if (voxel_left == 0)
                        {
                            add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,
                                vertex_position_offset, center_mesh_offset, voxel_scale,
                                &start, start,
                                voxel_face_indicies_left, voxel_face_indicies_left_length,
                                voxel_face_vertices_left, voxel_face_vertices_left_length);
                        }
                    #endif
                    #ifndef disable_voxel_right
                        unsigned char voxel_right = local_position.x == chunkSize->value.x - 1 ?
                            0 : chunk->value[int3_array_index(int3_right(local_position), chunkSize->value)];
                        if (voxel_right == 0)
                        {
                            add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,
                                vertex_position_offset, center_mesh_offset, voxel_scale,
                                &start, start,
                                voxel_face_indicies_right, voxel_face_indicies_right_length,
                                voxel_face_vertices_right, voxel_face_vertices_right_length);
                        }
                    #endif
                    #ifndef disable_voxel_down
                        // get side voxels
                        unsigned char voxel_down = local_position.y == 0 ?
                            0 : chunk->value[int3_array_index(int3_down(local_position), chunkSize->value)];
                        if (voxel_down == 0)
                        {
                            add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,
                                vertex_position_offset, center_mesh_offset, voxel_scale,
                                &start, start,
                                voxel_face_indicies_down, voxel_face_indicies_down_length,
                                voxel_face_vertices_down, voxel_face_vertices_down_length);
                        }
                    #endif*/
                    #ifndef disable_voxel_up
                        unsigned char voxel_up = local_position.y == chunkSize->value.y - 1 ?
                            0 : chunk->value[int3_array_index(int3_up(local_position), chunkSize->value)];
                        if (voxel_up == 0)
                        {
                            add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,
                                vertex_position_offset, center_mesh_offset, voxel_scale,
                                &start, start,
                                voxel_face_indicies_up, voxel_face_indicies_up_length,
                                voxel_face_vertices_up, voxel_face_vertices_up_length,
                                voxel_face_uvs_up);
                        }
                    #endif
                    /*#ifndef disable_voxel_back
                        unsigned char voxel_back = local_position.z == 0 ?
                            0 : chunk->value[int3_array_index(int3_back(local_position), chunkSize->value)];
                        if (voxel_back == 0)
                        {
                            add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,
                                vertex_position_offset, center_mesh_offset, voxel_scale,
                                &start, start,
                                voxel_face_indicies_back, voxel_face_indicies_back_length,
                                voxel_face_vertices_back, voxel_face_vertices_back_length);
                        }
                    #endif
                    #ifndef disable_voxel_front
                        unsigned char voxel_front = local_position.z == chunkSize->value.z - 1 ?
                            0 : chunk->value[int3_array_index(int3_front(local_position), chunkSize->value)];
                        if (voxel_front == 0)
                        {
                            add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,
                                vertex_position_offset, center_mesh_offset, voxel_scale,
                                &start, start,
                                voxel_face_indicies_front, voxel_face_indicies_front_length,
                                voxel_face_vertices_front, voxel_face_vertices_front_length);
                        }
                    #endif*/
                }
                // array_index++;
            }
        }
    }
}

//! Builds a mesh data from the chunk!
void ChunkUVsBuildSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    // printf("[ChunkBuildSystem] GenerateChunk was changed.\n");
    const ChunkDirty *entityDirtys = ecs_field(it, ChunkDirty, 1);
    const Chunk *chunks = ecs_field(it, Chunk, 2);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 3);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 4);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 5);
    MeshUVs *meshUVs = ecs_field(it, MeshUVs, 6);
    for (int i = 0; i < it->count; i++)
    {
        const ChunkDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value == 0)
        {
            continue;
        }
        printf("Building Chunk UVs Mesh [%lu]\n", (long int) it->entities[i]);
        const Chunk *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        MeshUVs *meshUVs2 = &meshUVs[i];
        build_chunk_mesh_uvs(chunk, chunkSize, meshIndicies2, meshVertices2, meshUVs2);
    }
}
ECS_SYSTEM_DECLARE(ChunkUVsBuildSystem);


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

                    // printf("Adding Voxel Mesh for [%ix%ix%i]\n", j, k, l);
                    // top face
                    /*int vertices_start = solid_voxels_count * verticies_per_voxel;
                    int indicies_start = solid_voxels_count * indicies_per_voxel;
                    float3 vertex_position_offset = float3_multiply_float(
                        float3_from_int3(local_position), voxel_scale);
                    for (int a = 0, b = indicies_start; a < indicies_per_voxel; a++, b++)
                    {
                        meshIndicies2->value[b] = voxel_cube_indicies[a] + vertices_start / 3;
                        //if (k == 0 && l == 0)
                            //   printf("    - index at [%i:%i] is [%i] from base [%i]\n", a, b, meshIndicies2->value[b], cubeIndicies[a]);
                    }
                    // top face
                    for (int a = 0, b = vertices_start; a < verticies_per_voxel2; a++, b = b + 3)
                    {
                        float3 vertex_position = voxel_cube_vertices[a]; // (float3) { cubeVertices[a + 0], cubeVertices[a + 1], cubeVertices[a + 2] };
                        vertex_position = float3_multiply_float(vertex_position, voxel_scale);          // scale vertex
                        vertex_position = float3_add(vertex_position, vertex_position_offset);   // offset vertex by voxel position in chunk
                        vertex_position = float3_add(vertex_position, center_mesh_offset);       // add total mesh offset
                        meshVertices2->value[b + 0] = vertex_position.x;
                        meshVertices2->value[b + 1] = vertex_position.y;
                        meshVertices2->value[b + 2] = vertex_position.z;
                        //if (k == 0 && l == 0)
                        //    printf("    - vertex at [%i:%i] is [%fx%fx%f]\n", a, b, vertex_position.x, vertex_position.y, vertex_position.z);
                    }
                    solid_voxels_count++;*/
                        // int vertices_start = solid_voxels_count * voxel_face_vertices_up_length * 3;
                        // int indicies_start = solid_voxels_count * voxel_face_indicies_up_length;