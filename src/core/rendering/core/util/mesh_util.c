void prefab_set_mesh_indicies(ecs_world_t *world, ecs_entity_t e, const int indicies[], int length) {
    MeshIndicies meshIndicies = { };
    initialize_memory_component_non_pointer(meshIndicies, int, length);
    memcpy(meshIndicies.value, indicies, length * sizeof(int));
    zox_set(e, MeshIndicies, { meshIndicies.length, meshIndicies.value });
}

void prefab_set_mesh2D_vertices(ecs_world_t *world, ecs_entity_t e, const float2 vertices[], int length) {
    MeshVertices2D meshVertices = { };
    initialize_memory_component_non_pointer(meshVertices, float2, length);
    memcpy(meshVertices.value, vertices, length * sizeof(float2));
    zox_set(e, MeshVertices2D, { meshVertices.length, meshVertices.value });
}

void prefab_set_mesh3D_vertices(ecs_world_t *world, ecs_entity_t e, const float2 vertices[], int length) {
    MeshVertices meshVertices = { };
    initialize_memory_component_non_pointer(meshVertices, float3, length);
    for (int i = 0; i < length; i++) meshVertices.value[i] = (float3) { vertices[i].x * 0.2f, vertices[i].y * 0.05f, 0 };
    zox_set(e, MeshVertices, { meshVertices.length, meshVertices.value });
    MeshColorRGBs meshColorRGBs = { };
    initialize_memory_component_non_pointer(meshColorRGBs, color_rgb, length);
    for (int i = 0; i < length; i++) meshColorRGBs.value[i] = (color_rgb) { 255, 255, 255 };
    zox_set(e, MeshColorRGBs, { meshColorRGBs.length, meshColorRGBs.value });
}


void prefab_set_mesh_uvs(ecs_world_t *world, ecs_entity_t e, const float2 uvs[], int length) {
    MeshUVs meshUVs = { };
    initialize_memory_component_non_pointer(meshUVs, float2, length);
    memcpy(meshUVs.value, uvs, length * sizeof(float2));
    zox_set(e, MeshUVs, { meshUVs.length, meshUVs.value });
}

void prefab_set_mesh_vertices(ecs_world_t *world, ecs_entity_t e, const float3 vertices[], int length) {
    MeshVertices meshVertices = { };
    initialize_memory_component_non_pointer(meshVertices, float3, length);
    memcpy(meshVertices.value, vertices, length * sizeof(float3));
    zox_set(e, MeshVertices, { meshVertices.length, meshVertices.value });
}

void scale_mesh2D_vertices(ecs_world_t *world, ecs_entity_t e, float2 scale2D) {
    MeshVertices2D *meshVertices2D = ecs_get_mut(world, e, MeshVertices2D);
    for (int i = 0; i < meshVertices2D->length; i++) float2_multiply_float2_p(&meshVertices2D->value[i], scale2D);
    ecs_modified(world, e, MeshVertices2D);
}

void scale_mesh2D_vertices_p(MeshVertices2D *meshVertices2D, float2 scale2D) {
    for (int i = 0; i < meshVertices2D->length; i++) float2_multiply_float2_p(&meshVertices2D->value[i], scale2D);
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