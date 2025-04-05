void Elementbar3DSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ElementBar, elementBars, 1)
    zox_field_in(ElementBarSize, elementBarSizes, 2)
    zox_field_in(Children, childrens, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Children, childrens, children)
        if (!children->length) {
            continue;
        }
        // ecs_entity_t front_bar = 0; // go through list to find frontbar
        const ecs_entity_t front_bar = children->value[0];
        if (!zox_valid(front_bar)) continue;
        zox_geter(front_bar, InitializeElement, initializeElement)
        if (initializeElement->value) {
            continue; // removing this breaks it?!?!
        }
        zox_field_e()
        if (!can_render_ui(world, e)) {
            continue; // disabled for now causes issues
        }
        zox_field_i(ElementBar, elementBars, elementBar)
        zox_field_i(ElementBarSize, elementBarSizes, elementBarSize)
        const float percentage = elementBar->value;
        const float2 scale = elementBarSize->value;
        const float left_offset = - scale.x * (1.0f - percentage) * 0.5f;
        if (zox_has(front_bar, MeshVertices)) {
            MeshDirty *meshDirty = zox_get_mut(front_bar, MeshDirty)
            if (meshDirty->value) {
                continue;
            }
            meshDirty->value = mesh_state_trigger2;
            zox_modified(front_bar, MeshDirty)
            zox_get_muter(front_bar, MeshVertices, meshVertices2)
            for (byte j = 0; j < 4; j++) meshVertices2->value[j] = (float3) { left_offset + square_vertices[j].x * scale.x * percentage, square_vertices[j].y * scale.y, 0 };
        }
    }
} zox_declare_system(Elementbar3DSystem)
