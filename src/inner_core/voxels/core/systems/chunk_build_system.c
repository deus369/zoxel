// set_mesh_indicies(world, e, cubeIndicies, 36);
// set_mesh_vertices(world, e, cubeVertices, 24);

//! Builds a mesh data from the chunk!
void ChunkBuildSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    // printf("[ChunkBuildSystem] GenerateChunk was changed.\n");
    const EntityDirty *entityDirtys = ecs_field(it, EntityDirty, 1);
    const Chunk *chunks = ecs_field(it, Chunk, 2);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 3);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 4);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 5);
    for (int i = 0; i < it->count; i++)
    {
        const EntityDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value == 0)
        {
            continue;
        }
        // printf("Building Chunk Mesh [%lu]\n", (long int) it->entities[i]);
        const Chunk *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        // go through and add a top face for each voxel position that is solid
        int array_index = 0;
        int solid_voxels_count = 0;
        for (int j = 0; j < chunkSize->value.x; j++)
        {
            for (int k = 0; k < chunkSize->value.y; k++)
            {
                for (int l = 0; l < chunkSize->value.y; l++)
                {
                    if (chunk->value[array_index] != 0)
                    {
                        // add faces - based on neighbor voxels.
                        solid_voxels_count++;
                    }
                    array_index++;
                }
            }
        }
        int indicies_per_voxel = 36;    // 6 * 6
        int verticies_per_voxel = 24;   // 8 * 3
        int verticies_per_voxel2 = 8;   // per vertex 3
        re_initialize_memory_component(meshIndicies2, int, solid_voxels_count * indicies_per_voxel);
        re_initialize_memory_component(meshVertices2, float, solid_voxels_count * verticies_per_voxel);
        float voxel_scale = overall_voxel_scale / ((float) chunkSize->value.x); // 16.0f;
        float3 center_mesh_offset = (float3) { - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };
        // printf("=== Voxel [%i] ===\n", solid_voxels_count);
        solid_voxels_count = 0;
        array_index = 0;
        for (int j = 0; j < chunkSize->value.x; j++)
        {
            for (int k = 0; k < chunkSize->value.y; k++)
            {
                for (int l = 0; l < chunkSize->value.z; l++)
                {
                    if (chunk->value[array_index] != 0)
                    {
                        // printf("Adding Voxel Mesh for [%ix%ix%i]\n", j, k, l);
                        // top face
                        int vertices_start = solid_voxels_count * verticies_per_voxel;
                        int indicies_start = solid_voxels_count * indicies_per_voxel;
                        float3 vertex_position_offset = float3_multiply_float((float3) { j, k, l }, voxel_scale);
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
                        solid_voxels_count++;
                    }
                    array_index++;
                }
            }
        }
    }
}
ECS_SYSTEM_DECLARE(ChunkBuildSystem);


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