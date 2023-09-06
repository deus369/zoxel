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
            if (deviceMode->value == zox_device_mode_keyboardmouse && ecs_has(world, device_entity, Mouse)) {
                const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                int2_add_int2_p(&raycaster->value, mouse->position);
            } else if (deviceMode->value == zox_device_mode_touchscreen && ecs_has(world, device_entity, Touchscreen)) {
                const Children *zevices = ecs_get(world, device_entity, Children);
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (ecs_has(world, zevice_entity, ZevicePointer)) {
                        const ZevicePointer *zevicePointer = ecs_get(world, zevice_entity, ZevicePointer);
                        if (devices_get_released_this_frame(zevicePointer->value) || devices_get_is_pressed(zevicePointer->value)) {
                            const ZevicePointerPosition *zevicePointerPosition = ecs_get(world, zevice_entity, ZevicePointerPosition);
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

/*const Touchscreen *touchscreen = ecs_get(world, device_entity, Touchscreen);
if (touchscreen->primary_touch.value.is_pressed || touchscreen->primary_touch.value.released_this_frame) {
    // int2_add_int2_p(&raycaster->value, touchscreen->primary_touch.position);
    raycaster->value = touchscreen->primary_touch.position;
} else {
    raycaster->value = (int2) { -10000, -10000 };
}*/