// animation system
void ElementActiveSystem(ecs_iter_t *it) {
    zox_field_in(ActiveState, activeStates, 1)
    zox_field_out(Brightness, brightnesss, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ActiveState, activeStates, activeState)
        zox_field_o(Brightness, brightnesss, brightness)
        if (activeState->value) brightness->value = ui_active_brightness;
        else brightness->value = ui_default_brightness;
    }
} zox_declare_system(ElementActiveSystem)
