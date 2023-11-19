// pushes mouse data into Raycaster component
// todo: check device mode here or device enabled states
void MouseRaycasterSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinks = ecs_field(it, DeviceLinks, 1);
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 2);
    Raycaster *raycasters = ecs_field(it, Raycaster, 3);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks2 = &deviceLinks[i];
        const DeviceMode *deviceMode = &deviceModes[i];
        Raycaster *raycaster = &raycasters[i];
        raycaster->value = int2_zero;
        for (int j = 0; j < deviceLinks2->length; j++) {
            ecs_entity_t device_entity = deviceLinks2->value[j];
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device_entity, Mouse)) {
                const Mouse *mouse = zox_get(device_entity, Mouse)
                int2_add_int2_p(&raycaster->value, mouse->position);
            } else if (deviceMode->value == zox_device_mode_touchscreen && zox_has(device_entity, Touchscreen)) {
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZevicePointer)) {
                        const ZevicePointer *zevicePointer = zox_get(zevice_entity, ZevicePointer)
                        if (devices_get_released_this_frame(zevicePointer->value) || devices_get_is_pressed(zevicePointer->value)) {
                            const ZevicePointerPosition *zevicePointerPosition = zox_get(zevice_entity, ZevicePointerPosition)
                            // raycaster->value = zevicePointerPosition->value;
                            int2_add_int2_p(&raycaster->value, zevicePointerPosition->value);
                        } else {
                            raycaster->value = (int2) { -10000, -10000 };
                        }
                        break;
                    }
                }
            }
        }
    }
} zox_declare_system(MouseRaycasterSystem)
