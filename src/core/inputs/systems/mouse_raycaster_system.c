// pushes mouse data into Raycaster component
void MouseRaycasterSystem(ecs_iter_t *it) {
    const DeviceLinks *deviceLinks = ecs_field(it, DeviceLinks, 1);
    Raycaster *raycasters = ecs_field(it, Raycaster, 2);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks2 = &deviceLinks[i];
        Raycaster *raycaster = &raycasters[i];
        for (int j = 0; j < deviceLinks2->length; j++) {
            ecs_entity_t device_entity = deviceLinks2->value[j];
            if (ecs_has(world, device_entity, Mouse)) {
                const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                raycaster->value = mouse->position;
                // break;
            } else if (ecs_has(world, device_entity, Touchscreen)) {
                const Touchscreen *touchscreen = ecs_get(world, device_entity, Touchscreen);
                if (touchscreen->primary_touch.value.is_pressed) {
                    raycaster->value = touchscreen->primary_touch.position;
                }
            }
        }
    }
}
zox_declare_system(MouseRaycasterSystem)