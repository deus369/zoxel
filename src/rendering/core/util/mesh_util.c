void prefab_set_mesh_indicies(ecs_world_t *world, ecs_entity_t e, const int indicies[], int length) {
    if (headless) return;
    if (!zox_has(e, MeshIndicies)) {
        zox_log("! [%lu] has no MeshIndicies\n")
        return;
    }
    zox_get_muter(e, MeshIndicies, meshIndicies)
    resize_memory_component(MeshIndicies, meshIndicies, int, length)
    memcpy(meshIndicies->value, indicies, length * sizeof(int));
}

void prefab_set_mesh2D_vertices(ecs_world_t *world, ecs_entity_t e, const float2 vertices[], int length) {
    if (headless) return;
    if (!zox_has(e, MeshVertices2D)) {
        zox_log("! [%lu] has no MeshVertices2D\n")
        return;
    }
    zox_get_muter(e, MeshVertices2D, meshVertices2D)
    resize_memory_component(MeshVertices2D, meshVertices2D, float2, length)
    memcpy(meshVertices2D->value, vertices, length * sizeof(float2));
}

void prefab_set_mesh3D_vertices(ecs_world_t *world, const ecs_entity_t e, const float2 vertices[], const int length, const float2 scale) {
    if (headless) return;
    if (!zox_has(e, MeshVertices)) {
        zox_log("! [%lu] has no MeshVertices\n")
        return;
    }
    // zox_get_muter(e, MeshVertices, meshVertices)
    MeshVertices *meshVertices = &((MeshVertices) { 0, NULL });
    resize_memory_component(MeshVertices, meshVertices, float3, length)
    for (int i = 0; i < length; i++) {
        meshVertices->value[i] = (float3) { vertices[i].x * scale.x, vertices[i].y * scale.y, 0 };
    }
    zox_prefab_set(e, MeshVertices, { meshVertices->length, meshVertices->value })
}

void prefab_set_mesh_colors_rgb(ecs_world_t *world, ecs_entity_t e, color_rgb color, int length) {
    if (headless) return;
    if (!zox_has(e, MeshColorRGBs)) {
        zox_log("! [%lu] has no MeshColorRGBs\n")
        return;
    }
    zox_get_muter(e, MeshColorRGBs, meshColorRGBs)
    resize_memory_component(MeshColorRGBs, meshColorRGBs, color_rgb, length)
    for (int i = 0; i < length; i++) meshColorRGBs->value[i] = color;
}

void prefab_set_mesh_vertices_float(ecs_world_t *world, ecs_entity_t e, const float vertices[], int length) {
    if (headless) return;
    if (!zox_has(e, MeshVertices)) {
        zox_log("! [%lu] has no MeshVertices\n")
        return;
    }
    zox_get_muter(e, MeshVertices, meshVertices)
    resize_memory_component(MeshVertices, meshVertices, float3, length)
    memcpy(meshVertices->value, vertices, length * sizeof(float));
}

void prefab_set_mesh_vertices_float3(ecs_world_t *world, ecs_entity_t e, const float3 vertices[], int length) {
    if (headless) return;
    if (!zox_has(e, MeshVertices)) {
        zox_log("! [%lu] has no MeshVertices\n")
        return;
    }
    zox_get_muter(e, MeshVertices, meshVertices)
    resize_memory_component(MeshVertices, meshVertices, float3, length)
    if (length > 0) memcpy(meshVertices->value, vertices, length * sizeof(float3));
}

void set_mesh_vertices_scale2D(MeshVertices2D *meshVertices2D, const float2 new_vertices[], const int length, const float2 scale2D) {
    resize_memory_component(MeshVertices2D, meshVertices2D, float2, length)
    if (length > 0) memcpy(meshVertices2D->value, new_vertices, length * sizeof(float2));
    for (int i = 0; i < length; i++) float2_multiply_float2_p(&meshVertices2D->value[i], scale2D);
}

void prefab_set_mesh_uvs_float(ecs_world_t *world, ecs_entity_t e, const float uvs[], int length) {
    if (headless) return;
    /*if (!zox_has(e, MeshUVs)) {
        zox_log("! [%lu] has no MeshUVs\n")
        return;
    }*/
    MeshUVs *meshUVs = &((MeshUVs) { 0, NULL });
    // zox_get_muter(e, MeshUVs, meshUVs)
    resize_memory_component(MeshUVs, meshUVs, float2, length)
    memcpy(meshUVs->value, uvs, length * sizeof(float));
    zox_prefab_set(e, MeshUVs, { meshUVs->length, meshUVs->value })
}

void prefab_set_mesh_uvs_float2(ecs_world_t *world, ecs_entity_t e, const float2 uvs[], int length) {
    if (headless) return;
    /*if (!zox_has(e, MeshUVs)) {
        zox_log("! [%lu] has no MeshUVs\n")
        return;
    }*/
    // zox_get_muter(e, MeshUVs, meshUVs)
    MeshUVs *meshUVs = &((MeshUVs) { 0, NULL });
    resize_memory_component(MeshUVs, meshUVs, float2, length)
    if (meshUVs->value) {
        memcpy(meshUVs->value, uvs, length * sizeof(float2));
    } else {
        zox_log("! meshUVs realloc failed")
    }
    zox_prefab_set(e, MeshUVs, { meshUVs->length, meshUVs->value })
}
