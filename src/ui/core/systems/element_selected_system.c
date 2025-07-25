void ElementSelectedSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(SelectState)
    zox_sys_out(Brightness)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(SelectState, selectState)
        zox_sys_o(Brightness, brightness)
        byte is_dragging = 0;
        if (zox_has(e, DraggableState)) {
            is_dragging = zox_get_value(e, DraggableState)
        }
        byte is_active = 0;
        if (zox_has(e, ActiveState)) {
            is_active = zox_get_value(e, ActiveState)
        }
        if (is_active) {
            brightness->value = ui_active_brightness;
        } else if (is_dragging) {
            brightness->value = ui_dragging_brightness;
        } else if (selectState->value) {
            brightness->value = ui_selected_brightness;
        } else {
            brightness->value = ui_default_brightness;
        }
    }
} zox_declare_system(ElementSelectedSystem)