void Elementbar3DSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ElementBar)
    zox_sys_in(ElementBarSize)
    zox_sys_in(Children)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Children, children)
        zox_sys_i(ElementBar, elementBar)
        zox_sys_i(ElementBarSize, elementBarSize)
        if (!children->length) {
            continue;
        }
        // entity front_bar = 0; // go through list to find frontbar
        const entity front_bar = children->value[0];
        if (!zox_valid(front_bar)) {
            continue;
        }
        zox_geter(front_bar, InitializeElement, initializeElement)
        if (initializeElement->value) {
            continue; // removing this breaks it?!?!
        }
        zox_sys_e()
        if (!can_render_ui(world, e)) {
            continue; // disabled for now causes issues
        }
        const float percentage = elementBar->value;
        const float2 scale = elementBarSize->value;
        const float left_offset = - scale.x * (1.0f - percentage) * 0.5f;
        if (zox_has(front_bar, MeshVertices)) {
            MeshDirty *meshDirty = zox_get_mut(front_bar, MeshDirty)
            if (meshDirty->value) {
                continue;
            }
            meshDirty->value = mesh_state_trigger;
            zox_modified(front_bar, MeshDirty)
            zox_get_muter(front_bar, MeshVertices, meshVertices2)
            for (byte j = 0; j < 4; j++) {
                meshVertices2->value[j] = (float3) { left_offset + square_vertices[j].x * scale.x * percentage, square_vertices[j].y * scale.y, 0 };
            }
            // zox_log_elements3D("+ updated frontbar [%lu]", it->entities[i])
        }
    }
} zoxd_system(Elementbar3DSystem)
