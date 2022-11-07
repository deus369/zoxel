void set_mesh_indicies_world(ecs_world_t *world, ecs_entity_t e, const int indicies[], int length)
{
    // printf("set_mesh_indicies length %i\n", length);
    MeshIndicies *meshIndicies = ecs_get_mut(world, e, MeshIndicies);
    initialize_memory_component(meshIndicies, int, length);
    for (int i = 0; i < meshIndicies->length; i++)
    {
        meshIndicies->value[i] = indicies[i];
        // printf("Index [%i] is [%i]\n", i, indicies[i]);
    }
    ecs_modified(world, e, MeshIndicies);
}

void set_mesh_vertices_world(ecs_world_t *world, ecs_entity_t e, const float vertices[], int length)
{
    // printf("set_mesh_vertices length %i\n", length);
    MeshVertices *meshVertices = ecs_get_mut(world, e, MeshVertices);
    initialize_memory_component(meshVertices, float, length);
    for (int i = 0; i < meshVertices->length; i++)
    {
        meshVertices->value[i] = vertices[i];
        // printf("Vertex [%i] is [%fx%fx%f]\n", i, vertices[i].x,  vertices[i].y, vertices[i].z);
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

void set_mesh_vertices(MeshVertices* meshVertices, const float vertices[], int length)
{
    re_initialize_memory_component(meshVertices, float, length);
    for (int i = 0; i < meshVertices->length; i++)
    {
        meshVertices->value[i] = vertices[i];
    }
}