void ElementBarSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;   // todo: make run on threads
    ecs_world_t *world = it->world;
    const ElementBar *elementBars = ecs_field(it, ElementBar, 1);
    const ElementBarSize *elementBarSizes = ecs_field(it, ElementBarSize, 2);
    MeshVertices *meshVertices3Ds = ecs_field(it, MeshVertices, 3);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 4);
    for (int i = 0; i < it->count; i++) {
        ecs_entity_t e = it->entities[i];
        const ElementBar *elementBar = &elementBars[i];
        const ElementBarSize *elementBarSize = &elementBarSizes[i];
        MeshDirty *meshDirty = &meshDirtys[i];
        MeshVertices *meshVertices3D = &meshVertices3Ds[i];
        if (meshDirty->value) continue;
        float2 scale = elementBarSize->value;
        // todo: get scale from component
        float left_offset = - scale.x * (1.0f - elementBar->value) * 0.5f;
        scale.x *= elementBar->value;
        for (int i = 0; i < 4; i++) meshVertices3D->value[i] = (float3) { left_offset + square_vertices[i].x * scale.x, square_vertices[i].y * scale.y, 0 };
        meshDirty->value = 1;
    }
} zox_declare_system(ElementBarSystem)