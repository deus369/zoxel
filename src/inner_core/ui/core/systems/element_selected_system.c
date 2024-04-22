void ElementSelectedSystem(ecs_iter_t *it) {
    zox_field_in(SelectState, selectStates, 2)
    zox_field_out(Brightness, brightnesss, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(SelectState, selectStates, selectState)
        zox_field_i_out(Brightness, brightnesss, brightness)
        if (selectState->value) brightness->value = ui_selected_brightness;
        else brightness->value = ui_default_brightness;
    }
} zox_declare_system(ElementSelectedSystem)
