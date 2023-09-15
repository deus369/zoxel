void ElementBarSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    // zoxel_log(" > updating element bars\n");
    ecs_world_t *world = it->world;
    const ElementBar *elementBars = ecs_field(it, ElementBar, 1);
    MeshVertices *meshVertices3Ds = ecs_field(it, MeshVertices, 2);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 3);
    for (int i = 0; i < it->count; i++) {
        ecs_entity_t e = it->entities[i];
        const ElementBar *elementBar = &elementBars[i];
        MeshDirty *meshDirty = &meshDirtys[i];
        MeshVertices *meshVertices3D = &meshVertices3Ds[i];
        if (meshDirty->value) continue;
        float2 mesh_scale = (float2) { 0.17f, 0.028f };
        // prefab_set_mesh3D_vertices(world, e, square_vertices, 4, mesh_scale);
        float left_offset = - mesh_scale.x * (1.0f - elementBar->value) * 0.5f;
        mesh_scale.x *= elementBar->value;
        for (int i = 0; i < 4; i++) meshVertices3D->value[i] = (float3) { left_offset + square_vertices[i].x * mesh_scale.x, square_vertices[i].y * mesh_scale.y, 0 };
        meshDirty->value = 1;
    }
} zox_declare_system(ElementBarSystem)