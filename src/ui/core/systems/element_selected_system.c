// animation system
void ElementSelectedSystem(ecs_iter_t *it) {
    zox_field_in(SelectState, selectStates, 2)
    zox_field_out(Brightness, brightnesss, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(SelectState, selectStates, selectState)
        zox_field_o(Brightness, brightnesss, brightness)
        // todo: move these to new systems?
        unsigned char is_dragging = 0;
        if (zox_has(e, DraggableState)) {
            is_dragging = zox_get_value(e, DraggableState)
        }
        unsigned char is_active = 0;
        if (zox_has(e, ActiveState)) is_active = zox_get_value(e, ActiveState)
        if (is_active) brightness->value = ui_active_brightness;
        else if (is_dragging) brightness->value = ui_dragging_brightness;
        else if (selectState->value) brightness->value = ui_selected_brightness;
        else brightness->value = ui_default_brightness;
    }
} zox_declare_system(ElementSelectedSystem)
