// todo: change this to work with player, cameraLinks, and deviceLinks
void FreeCameraToggleSystem(ecs_iter_t *it) {
    zox_iter_world()
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const CameraLink *cameraLinks = ecs_field(it, CameraLink, 3);
    for (int i = 0; i < it->count; i++) {
        // todo: use player GameLink here
        const GameState *gameState = zox_get(local_game, GameState)
        if (gameState->value != zoxel_game_state_playing) continue;
        const CameraLink *cameraLink = &cameraLinks[i];
        if (cameraLink->value == 0) continue;
        const CanFreeRoam *canFreeRoam = zox_get(cameraLink->value, CanFreeRoam)
        if (canFreeRoam->value == 0) continue;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        unsigned char is_triggered = 0;
        ecs_entity_t mouse_entity = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Mouse)) {
                const Mouse *mouse = zox_get(device_entity, Mouse)
                if (mouse->right.pressed_this_frame) is_triggered = 1;
                mouse_entity = device_entity;
            }
        }
        if (is_triggered && mouse_entity != 0) {
            const MouseLock *mouseLock = zox_get(mouse_entity, MouseLock)
            unsigned char new_value = !mouseLock->value;
            // zoxel_log(" > free camera toggled [%s]\n", new_value ? "on" : "off");
            zox_set(mouse_entity, MouseLock, { new_value })
            zox_set(cameraLink->value, FreeRoam, { new_value })
        }
    }
} zox_declare_system(FreeCameraToggleSystem)
