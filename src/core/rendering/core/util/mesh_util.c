void prefab_set_mesh_indicies(ecs_world_t *world, ecs_entity_t e, const int indicies[], int length) {
    if (headless) return;
    MeshIndicies *meshIndicies = zox_get_mut(e, MeshIndicies)
    resize_memory_component(MeshIndicies, meshIndicies, int, length)
    memcpy(meshIndicies->value, indicies, length * sizeof(int));
    zox_modified(e, MeshIndicies);
}

void prefab_set_mesh2D_vertices(ecs_world_t *world, ecs_entity_t e, const float2 vertices[], int length) {
    if (headless) return;
    MeshVertices2D *meshVertices2D = zox_get_mut(e, MeshVertices2D)
    resize_memory_component(MeshVertices2D, meshVertices2D, float2, length)
    memcpy(meshVertices2D->value, vertices, length * sizeof(float2));
    zox_modified(e, MeshVertices2D)
}

void prefab_set_mesh_uvs(ecs_world_t *world, ecs_entity_t e, const float2 uvs[], int length) {
    if (headless) return;
    MeshUVs *meshUVs = zox_get_mut(e, MeshUVs)
    resize_memory_component(MeshUVs, meshUVs, float2, length)
    memcpy(meshUVs->value, uvs, length * sizeof(float2));
    zox_modified(e, MeshUVs)
}

void prefab_set_mesh3D_vertices(ecs_world_t *world, const ecs_entity_t e, const float2 vertices[], const int length, const float2 scale) {
    if (headless) return;
    MeshVertices *meshVertices = zox_get_mut(e, MeshVertices)
    resize_memory_component(MeshVertices, meshVertices, float3, length)
    for (int i = 0; i < length; i++) meshVertices->value[i] = (float3) { vertices[i].x * scale.x, vertices[i].y * scale.y, 0 };
    zox_modified(e, MeshVertices)
}

void prefab_set_mesh_colors_rgb(ecs_world_t *world, ecs_entity_t e, color_rgb color, int length) {
    if (headless) return;
    MeshColorRGBs *meshColorRGBs = zox_get_mut(e, MeshColorRGBs)
    resize_memory_component(MeshColorRGBs, meshColorRGBs, color_rgb, length)
    for (int i = 0; i < length; i++) meshColorRGBs->value[i] = color;
    zox_modified(e, MeshColorRGBs)
}

void prefab_set_mesh_vertices(ecs_world_t *world, ecs_entity_t e, const float vertices[], int length) {
    if (headless) return;
    MeshVertices *meshVertices = zox_get_mut(e, MeshVertices)
    resize_memory_component(MeshVertices, meshVertices, float3, length)
    memcpy(meshVertices->value, vertices, length * sizeof(float));
    zox_modified(e, MeshVertices)
}

void set_mesh_vertices_scale2D(MeshVertices2D *meshVertices2D, const float2 new_vertices[], const int length, const float2 scale2D) {
    resize_memory_component(MeshVertices2D, meshVertices2D, float2, length)
    memcpy(meshVertices2D->value, new_vertices, length * sizeof(float2));
    for (int i = 0; i < length; i++) float2_multiply_float2_p(&meshVertices2D->value[i], scale2D);
}
