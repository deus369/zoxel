void FreeCameraToggleSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DeviceLinks)
    zox_sys_in(CameraLink)
    zox_sys_in(GameLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DeviceLinks, deviceLinks)
        zox_sys_i(CameraLink, cameraLink)
        zox_sys_i(GameLink, gameLink)
        if (!gameLink->value) continue;
        const byte game_state = zox_get_value(gameLink->value, GameState)
        if (game_state != zox_game_playing) continue;
        if (cameraLink->value == 0) continue;
        const CanRoam *canRoam = zox_get(cameraLink->value, CanRoam)
        if (!canRoam->value) continue;
        byte is_triggered = 0;
        ecs_entity_t mouse = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device) || zox_gett_value(device, DeviceDisabled)) {
                continue;
            }
            if (zox_has(device, Mouse)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (zox_has(zevice, ZevicePointerRight)) {
                        const byte click = zox_get_value(zevice, ZevicePointerRight)
                        if (devices_get_pressed_this_frame(click)) is_triggered = 1;
                        mouse = device;
                    }
                }
            }
        }
        if (is_triggered && mouse != 0) {
            const byte mouse_locked = zox_get_value(mouse, MouseLock)
            byte new_value = !mouse_locked;
            zox_set(mouse, MouseLock, { new_value })
            zox_set(cameraLink->value, CanRoam, { new_value ? 2 : 1 })
            // zox_log(" > camera state [%s]\n", new_value ? "roaming" : "locked")
        }
    }
} zoxd_system(FreeCameraToggleSystem)
