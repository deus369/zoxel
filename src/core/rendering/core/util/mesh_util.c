void set_mesh_indicies_world(ecs_world_t *world, ecs_entity_t e, const int indicies[], int length) {
    MeshIndicies *meshIndicies = ecs_get_mut(world, e, MeshIndicies);
    re_initialize_memory_component(meshIndicies, int, length);
    for (int i = 0; i < meshIndicies->length; i++) {
        meshIndicies->value[i] = indicies[i];
    }
    ecs_modified(world, e, MeshIndicies);
}

void set_mesh_vertices_world_scale2D(ecs_world_t *world, ecs_entity_t e, const float2 vertices[], int length, float2 scale2D) {
    MeshVertices2D *meshVertices = ecs_get_mut(world, e, MeshVertices2D);
    re_initialize_memory_component(meshVertices, float2, length);
    for (int i = 0; i < meshVertices->length; i++) {
        meshVertices->value[i] = vertices[i];
        meshVertices->value[i].x *= scale2D.x;
        meshVertices->value[i].x -= scale2D.x / 2.0f;
        meshVertices->value[i].y *= scale2D.y;
        meshVertices->value[i].y -= scale2D.y / 2.0f;
    }
    ecs_modified(world, e, MeshVertices2D);
}

void set_mesh_vertices_world(ecs_world_t *world, ecs_entity_t e, const float3 vertices[], int length) {
    MeshVertices *meshVertices = ecs_get_mut(world, e, MeshVertices);
    initialize_memory_component(meshVertices, float3, length);
    for (int i = 0; i < meshVertices->length; i++) {
        meshVertices->value[i] = (float3) { vertices[i].x, vertices[i].y, vertices[i].z };
    }
    ecs_modified(world, e, MeshVertices);
}

void set_mesh_indicies(MeshIndicies* meshIndicies, const int indicies[], int length) {
    // printf("2 - MeshIndicies: %i\n", meshIndicies->length);
    re_initialize_memory_component(meshIndicies, int, length);
    for (int i = 0; i < meshIndicies->length; i++) {
        meshIndicies->value[i] = indicies[i];
    }
}