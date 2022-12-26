void set_mesh_indicies_world(ecs_world_t *world, ecs_entity_t e, const int indicies[], int length)
{
    MeshIndicies *meshIndicies = ecs_get_mut(world, e, MeshIndicies);
    re_initialize_memory_component(meshIndicies, int, length);
    for (int i = 0; i < meshIndicies->length; i++)
    {
        meshIndicies->value[i] = indicies[i];
    }
    ecs_modified(world, e, MeshIndicies);
}

void set_mesh_vertices_world_scale2D(ecs_world_t *world, ecs_entity_t e, const float2 vertices[], int length, float2 scale2D)
{
    MeshVertices2D *meshVertices = ecs_get_mut(world, e, MeshVertices2D);
    re_initialize_memory_component(meshVertices, float2, length);
    for (int i = 0; i < meshVertices->length; i++)
    {
        meshVertices->value[i] = vertices[i];
        meshVertices->value[i].x *= scale2D.x;
        meshVertices->value[i].x -= scale2D.x / 2.0f;
        meshVertices->value[i].y *= scale2D.y;
        meshVertices->value[i].y -= scale2D.y / 2.0f;
    }
    ecs_modified(world, e, MeshVertices2D);
}

void set_mesh_uvs(ecs_world_t *world, ecs_entity_t e, const float2 uvs[], int length)
{
    MeshUVs *meshUVs = ecs_get_mut(world, e, MeshUVs);
    re_initialize_memory_component(meshUVs, float2, length);
    for (int i = 0; i < length; i++)
    {
        meshUVs->value[i] = uvs[i];
    }
    // memcpy(meshUVs->value, uvs, length);
    ecs_modified(world, e, MeshUVs);
}

void set_mesh_vertices_world(ecs_world_t *world, ecs_entity_t e, const float3 vertices[], int length)
{
    MeshVertices *meshVertices = ecs_get_mut(world, e, MeshVertices);
    initialize_memory_component(meshVertices, float3, length);
    for (int i = 0; i < meshVertices->length; i++)
    {
        meshVertices->value[i] = vertices[i];
    }
    ecs_modified(world, e, MeshVertices);
}

void set_mesh_indicies(MeshIndicies* meshIndicies, const int indicies[], int length)
{
    printf("2 - MeshIndicies: %i\n", meshIndicies->length);
    re_initialize_memory_component(meshIndicies, int, length);
    for (int i = 0; i < meshIndicies->length; i++)
    {
        meshIndicies->value[i] = indicies[i];
    }
}

/*void set_mesh_vertices(MeshVertices* meshVertices, const float3 vertices[], int length)
{
    re_initialize_memory_component(meshVertices, float, length);
    for (int i = 0; i < meshVertices->length; i++)
    {
        meshVertices->value[i] = vertices[i];
    }
}*/
            /*if (i % 2 == 0)
            {
                meshVertices->value[i] *= scale2D.x;
                meshVertices->value[i] -= scale2D.x / 2.0f;
            }
            else
            {
                meshVertices->value[i] *= scale2D.y;
                meshVertices->value[i] -= scale2D.y / 2.0f;
            }*/