// todo: add raycaster onto each pointer zevice (for multiple fingers) - refactor from player entity and add Raycaster onto each zevice_pointer! This way we can click buttons while using joystick on the other finger
/*
void MouseRaycasterSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinks, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_out(Raycaster, raycasters, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DeviceLinks, deviceLinks, deviceLinks2)
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        zox_field_o(Raycaster, raycasters, raycaster)
        raycaster->value = int2_zero;
        for (int j = 0; j < deviceLinks2->length; j++) {
            const ecs_entity_t device = deviceLinks2->value[j];
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device, Mouse)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (!zox_has(zevice, ZevicePointer)) continue;
                    const int2 position = zox_get_value(zevice, ZevicePointerPosition)
                    int2_add_int2_p(&raycaster->value, position);
                }
            } else if (deviceMode->value == zox_device_mode_touchscreen && zox_has(device, Touchscreen)) {
                const Children *zevices = zox_get(device, Children)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (zox_has(zevice, ZevicePointer)) {
                        const ZevicePointer *zevicePointer = zox_get(zevice, ZevicePointer)
                        if (devices_get_released_this_frame(zevicePointer->value) || devices_get_is_pressed(zevicePointer->value)) {
                            const ZevicePointerPosition *zevicePointerPosition = zox_get(zevice, ZevicePointerPosition)
                            int2_add_int2_p(&raycaster->value, zevicePointerPosition->value);
                            // zox_log(" > player raycaster set to [%ix%i]\n", zevicePointerPosition->value.x, zevicePointerPosition->value.y)
                        } else {
                            raycaster->value = (int2) { -10000, -10000 };
                        }
                        break;
                    }
                }
            }
        }
    }
} zoxd_system(MouseRaycasterSystem)
*/