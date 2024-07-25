void FreeCameraToggleSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(CameraLink, cameraLinks, 2)
    zox_field_in(GameLink, gameLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(GameLink, gameLinks, gameLink)
        if (!gameLink->value) continue;
        const unsigned char game_state = zox_get_value(gameLink->value, GameState)
        if (game_state != zox_game_playing) continue;
        zox_field_i(CameraLink, cameraLinks, cameraLink)
        if (cameraLink->value == 0) continue;
        const CanRoam *canRoam = zox_get(cameraLink->value, CanRoam)
        if (!canRoam->value) continue;
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        unsigned char is_triggered = 0;
        ecs_entity_t mouse = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (zox_has(device, Mouse)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (zox_has(zevice, ZevicePointerRight)) {
                        const unsigned char click = zox_get_value(zevice, ZevicePointerRight)
                        if (devices_get_pressed_this_frame(click)) is_triggered = 1;
                        mouse = device;
                    }
                }
            }
        }
        if (is_triggered && mouse != 0) {
            const unsigned char mouse_locked = zox_get_value(mouse, MouseLock)
            unsigned char new_value = !mouse_locked;
            zox_set(mouse, MouseLock, { new_value })
            zox_set(cameraLink->value, CanRoam, { new_value ? 2 : 1 })
            zox_log(" > camera state [%s]\n", new_value ? "roaming" : "locked")
        }
    }
} zox_declare_system(FreeCameraToggleSystem)
