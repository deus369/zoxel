void set_mesh_indicies_world(ecs_world_t *world, ecs_entity_t e, const int indicies[], int length) {
    MeshIndicies *meshIndicies = ecs_get_mut(world, e, MeshIndicies);
    re_initialize_memory_component(meshIndicies, int, length);
    for (int i = 0; i < meshIndicies->length; i++) {
        meshIndicies->value[i] = indicies[i];
    }
    ecs_modified(world, e, MeshIndicies);
}

void set_mesh2D_vertices_world(ecs_world_t *world, ecs_entity_t e, const float2 vertices[], int length) {
    MeshVertices2D *meshVertices = ecs_get_mut(world, e, MeshVertices2D);
    re_initialize_memory_component(meshVertices, float2, length);
    for (int i = 0; i < meshVertices->length; i++) {
        meshVertices->value[i] = vertices[i];
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

void scale_mesh2D_vertices(ecs_world_t *world, ecs_entity_t e, float2 scale2D) {
    MeshVertices2D *meshVertices2D = ecs_get_mut(world, e, MeshVertices2D);
    for (int i = 0; i < meshVertices2D->length; i++) {
        float2_multiply_float2_p(&meshVertices2D->value[i], scale2D);
    }
    ecs_modified(world, e, MeshVertices2D);
}

void set_mesh_vertices_world_scale2D(ecs_world_t *world, ecs_entity_t e, const float2 vertices[], int length, float2 scale2D) {
    MeshVertices2D *meshVertices2D = ecs_get_mut(world, e, MeshVertices2D);
    re_initialize_memory_component(meshVertices2D, float2, length);
    for (int i = 0; i < meshVertices2D->length; i++) {
        meshVertices2D->value[i] = vertices[i];
        float2_multiply_float2_p(&meshVertices2D->value[i], scale2D);
    }
    ecs_modified(world, e, MeshVertices2D);
}

void set_mesh_indicies(MeshIndicies* meshIndicies, const int indicies[], int length) {
    re_initialize_memory_component(meshIndicies, int, length);
    for (int i = 0; i < meshIndicies->length; i++) {
        meshIndicies->value[i] = indicies[i];
    }
}