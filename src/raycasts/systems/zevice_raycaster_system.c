// todo: add raycaster onto each pointer zevice (for multiple fingers) - refactor from player entity and add Raycaster onto each zevice_pointer! This way we can click buttons while using joystick on the other finger

void ZeviceRaycasterSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(ZevicePointerPosition)
    zox_sys_out(Raycaster)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ZevicePointerPosition, zevicePointerPosition)
        zox_sys_o(Raycaster, raycaster)
        // const byte click_value = zevicePointer->value;
        /*if (!(devices_get_released_this_frame(click_value) || devices_get_is_pressed(click_value))) {
            raycaster->value = (int2) { -10000, -10000 };
        } else {
            raycaster->value = zevicePointerPosition->value;
        }*/
        raycaster->value = zevicePointerPosition->value;
    }
} zox_declare_system(ZeviceRaycasterSystem)
