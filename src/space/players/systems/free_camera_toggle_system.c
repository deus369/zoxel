// todo: change this to work with player, cameraLinks, and deviceLinks
void FreeCameraToggleSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const CameraLink *cameraLinks = ecs_field(it, CameraLink, 3);
    for (int i = 0; i < it->count; i++) {
        const CameraLink *cameraLink = &cameraLinks[i];
        if (cameraLink->value == 0) continue;
        const CanFreeRoam *canFreeRoam = ecs_get(world, cameraLink->value, CanFreeRoam);
        if (canFreeRoam->value == 0) continue;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        unsigned char is_triggered = 0;
        ecs_entity_t mouse_entity = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Mouse)) {
                const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                if (mouse->left.pressed_this_frame) is_triggered = 1;
                mouse_entity = device_entity;
            }
        }
        if (is_triggered && mouse_entity != 0) {
            const MouseLock *mouseLock = ecs_get(world, mouse_entity, MouseLock);
            unsigned char new_value = !mouseLock->value;
            zoxel_log(" > free camera toggled [%s]\n", new_value ? "on" : "off");
            zox_set_only(mouse_entity, MouseLock, { new_value })
            zox_set_only(cameraLink->value, FreeRoam, { new_value })
        }
    }
} zox_declare_system(FreeCameraToggleSystem)

/*if (ecs_has(world, device_entity, Keyboard)) {
    const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
    if (keyboard->space.is_pressed) is_triggered = 1;
} else if (ecs_has(world, device_entity, Gamepad)) {
    const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
    if (gamepad->a.pressed_this_frame) is_triggered = 1;
}*/
    /*ecs_iter_t cameraIter = ecs_query_iter(it->world, it->ctx);
    ecs_query_next(&cameraIter);
    if (cameraIter.count == 0) return;
    const Mouse *mouses = ecs_field(it, Mouse, 1);
    MouseLock *mouseLocks = ecs_field(it, MouseLock, 2);
    const CanFreeRoam *canFreeRoams = ecs_field(&cameraIter, CanFreeRoam, 2);
    FreeRoam *freeRoams = ecs_field(&cameraIter, FreeRoam, 3);
    for (int i = 0; i < it->count; i++) {
        const Mouse *mouse = &mouses[i];
        if (mouse->left.pressed_this_frame || mouse->right.pressed_this_frame) {
            zoxel_log(" > clickity clicky click\n");
            MouseLock *mouseLock = &mouseLocks[i];
            unsigned char new_value = !mouseLock->value;
            // zoxel_log(" > free camera toggled [%s]\n", mouseLock->value ? "on" : "off");
            for (int j = 0; j < cameraIter.count; j++) {
                const CanFreeRoam *canFreeRoam = &canFreeRoams[j];
                if (canFreeRoam->value) {
                    FreeRoam *freeRoam = &freeRoams[j];
                    mouseLock->value = new_value;
                    freeRoam->value = new_value;
                    zoxel_log(" > free camera toggled [%s]\n", new_value ? "on" : "off");
                } else {
                    zoxel_log(" > canot free roam [%lu]\n", cameraIter.entities[j]);
                }
            }
        }
    }*/