// reset each zevice in a system, on EcsOnLoad
void ZeviceButtonResetSystem(ecs_iter_t *it) {
    zox_field_out(ZeviceButton, zeviceButtons, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(ZeviceButton, zeviceButtons, zeviceButton)
        reset_device_button(zeviceButton);
    }
} zox_declare_system(ZeviceButtonResetSystem)
