void ElementBarSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;   // todo: make run on threads
    ecs_world_t *world = it->world;
    const ElementBar *elementBars = ecs_field(it, ElementBar, 1);
    const ElementBarSize *elementBarSizes = ecs_field(it, ElementBarSize, 2);
    const Children *childrens = ecs_field(it, Children, 3);
    for (int i = 0; i < it->count; i++) {
        const Children *childrenss = &childrens[i];
        if (childrenss->length == 0) continue;
        ecs_entity_t dirty_bar = childrenss->value[0];
        MeshDirty *meshDirty = ecs_get_mut(world, dirty_bar, MeshDirty);
        if (meshDirty->value) continue;
        ecs_entity_t e = it->entities[i];
        if (!can_render_ui(world, e)) continue;
        const ElementBar *elementBar = &elementBars[i];
        const ElementBarSize *elementBarSize = &elementBarSizes[i];
        MeshVertices *meshVertices = ecs_get_mut(world, dirty_bar, MeshVertices);
        float2 scale = elementBarSize->value;
        float left_offset = - scale.x * (1.0f - elementBar->value) * 0.5f;
        scale.x *= elementBar->value;
        for (unsigned char j = 0; j < 4; j++) meshVertices->value[j] = (float3) { left_offset + square_vertices[j].x * scale.x, square_vertices[j].y * scale.y, 0 };
        meshDirty->value = 1;
        ecs_modified(world, dirty_bar, MeshDirty);
        ecs_modified(world, dirty_bar, MeshVertices);
        // zoxel_log("         = new elementBar value is: %f\n", elementBar->value);
    }
} zox_declare_system(ElementBarSystem)

    // MeshVertices *meshVertices3Ds = ecs_field(it, MeshVertices, 3);
    // MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 3);
        // MeshVertices *meshVertices = &meshVertices3Ds[i];
        // MeshDirty *meshDirty = &meshDirtys[i];