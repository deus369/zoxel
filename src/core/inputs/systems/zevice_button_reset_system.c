// reset each zevice in a system, on EcsOnLoad
// make extract system too, link the sdl joystick to the reset systems

void ZeviceButtonResetSystem(ecs_iter_t *it) {
    ZeviceButton *zeviceButtons = ecs_field(it, ZeviceButton, 1);
    for (int i = 0; i < it->count; i++) {
        ZeviceButton *zeviceButton = &zeviceButtons[i];
        reset_device_button(zeviceButton);
    }
} zox_declare_system(ZeviceButtonResetSystem)