// animation system
void ElementActiveSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(ActiveState)
    zox_sys_out(Brightness)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ActiveState, activeState)
        zox_sys_o(Brightness, brightness)
        if (activeState->value) {
            brightness->value = ui_active_brightness;
        } else {
            brightness->value = ui_default_brightness;
        }
    }
} zox_declare_system(ElementActiveSystem)