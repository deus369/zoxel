void prefab_set_mesh_indicies(ecs_world_t *world, ecs_entity_t e, const int indicies[], int length) {
    if (headless) {
        return;
    }
    if (!zox_has(e, MeshIndicies)) {
        zox_log_error("[%lu] has no MeshIndicies", e);
        return;
    }
    MeshIndicies *meshIndicies = &((MeshIndicies) { 0, NULL });
    resize_memory_component(MeshIndicies, meshIndicies, int, length)
    memcpy(meshIndicies->value, indicies, length * sizeof(int));
    zox_prefab_set(e, MeshIndicies, { meshIndicies->length, meshIndicies->value })
}

void prefab_set_mesh2D_vertices(ecs_world_t *world, ecs_entity_t e, const float2 *vertices, int length) {
    if (headless || !vertices) {
        return;
    }
    MeshVertices2D *meshVertices2D = &((MeshVertices2D) { 0, NULL });
    resize_memory_component(MeshVertices2D, meshVertices2D, float2, length)
    memcpy(meshVertices2D->value, vertices, length * sizeof(float2));
    zox_prefab_set(e, MeshVertices2D, { meshVertices2D->length, meshVertices2D->value })
}

void prefab_set_mesh3D_vertices(ecs_world_t *world, const ecs_entity_t e, const float2 vertices[], const int length, const float2 scale) {
    if (headless) {
        return;
    }
    zox_geter(e, MeshVertices, oldVertices)
    if (oldVertices->value) {
        free(oldVertices->value);
    }
    MeshVertices *meshVertices = &((MeshVertices) { 0, NULL });
    resize_memory_component(MeshVertices, meshVertices, float3, length)
    for (int i = 0; i < length; i++) {
        meshVertices->value[i] = (float3) { vertices[i].x * scale.x, vertices[i].y * scale.y, 0 };
    }
    zox_prefab_set(e, MeshVertices, { meshVertices->length, meshVertices->value })
}

void prefab_set_mesh_colors_rgb(ecs_world_t *world, ecs_entity_t e, color_rgb color, int length) {
    if (headless) {
        return;
    }
    MeshColorRGBs *meshColorRGBs = &((MeshColorRGBs) { 0, NULL });
    resize_memory_component(MeshColorRGBs, meshColorRGBs, color_rgb, length)
    for (int i = 0; i < length; i++) meshColorRGBs->value[i] = color;
    zox_prefab_set(e, MeshColorRGBs, { meshColorRGBs->length, meshColorRGBs->value })
}

void prefab_set_mesh_vertices_float(ecs_world_t *world, ecs_entity_t e, const float vertices[], int length) {
    if (headless) {
        return;
    }
    MeshVertices *meshVertices = &((MeshVertices) { 0, NULL });
    resize_memory_component(MeshVertices, meshVertices, float3, length)
    memcpy(meshVertices->value, vertices, length * sizeof(float));
    zox_prefab_set(e, MeshVertices, { meshVertices->length, meshVertices->value })
}

void prefab_set_mesh_vertices_float3(ecs_world_t *world, ecs_entity_t e, const float3 vertices[], int length) {
    if (headless) {
        return;
    }
    MeshVertices *meshVertices = &((MeshVertices) { 0, NULL });
    resize_memory_component(MeshVertices, meshVertices, float3, length)
    if (length > 0) memcpy(meshVertices->value, vertices, length * sizeof(float3));
    zox_prefab_set(e, MeshVertices, { meshVertices->length, meshVertices->value })
}

void set_mesh_vertices_scale2D(MeshVertices2D *meshVertices2D, const float2 new_vertices[], const int length, const float2 scale2D) {
    resize_memory_component(MeshVertices2D, meshVertices2D, float2, length)
    if (length > 0) {
        memcpy(meshVertices2D->value, new_vertices, length * sizeof(float2));
    }
    for (int i = 0; i < length; i++) {
        float2_multiply_float2_p(&meshVertices2D->value[i], scale2D);
    }
}

void prefab_set_mesh_uvs_float(ecs_world_t *world, ecs_entity_t e, const float uvs[], int length) {
    if (headless) {
        return;
    }
    MeshUVs *meshUVs = &((MeshUVs) { 0, NULL });
    resize_memory_component(MeshUVs, meshUVs, float2, length)
    memcpy(meshUVs->value, uvs, length * sizeof(float));
    zox_prefab_set(e, MeshUVs, { meshUVs->length, meshUVs->value })
}

void prefab_set_mesh_uvs_float2(ecs_world_t *world, ecs_entity_t e, const float2 uvs[], int length) {
    if (headless) {
        return;
    }
    MeshUVs *meshUVs = &((MeshUVs) { 0, NULL });
    resize_memory_component(MeshUVs, meshUVs, float2, length)
    if (meshUVs->value) {
        memcpy(meshUVs->value, uvs, length * sizeof(float2));
    } else {
        zox_log_error("meshUVs realloc failed")
    }
    zox_prefab_set(e, MeshUVs, { meshUVs->length, meshUVs->value })
}
