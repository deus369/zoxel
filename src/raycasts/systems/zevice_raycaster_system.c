// todo: add raycaster onto each pointer zevice (for multiple fingers) - refactor from player entity and add Raycaster onto each zevice_pointer! This way we can click buttons while using joystick on the other finger

void ZeviceRaycasterSystem(ecs_iter_t *it) {
    // zox_field_world()
    zox_field_in(ZevicePointerPosition, zevicePointerPositions, 1)
    // zox_field_in(ZevicePointer, zevicePointers, 2)
    zox_field_out(Raycaster, raycasters, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ZevicePointerPosition, zevicePointerPositions, zevicePointerPosition)
        // zox_field_i(ZevicePointer, zevicePointers, zevicePointer)
        zox_field_o(Raycaster, raycasters, raycaster)
        // const byte click_value = zevicePointer->value;
        /*if (!(devices_get_released_this_frame(click_value) || devices_get_is_pressed(click_value))) {
            raycaster->value = (int2) { -10000, -10000 };
        } else {
            raycaster->value = zevicePointerPosition->value;
        }*/
        raycaster->value = zevicePointerPosition->value;
    }
} zox_declare_system(ZeviceRaycasterSystem)
