void PlayerToggleCameraSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const CharacterLink *characterLinks = ecs_field(it, CharacterLink, 3);
    for (int i = 0; i < it->count; i++) {
        const CharacterLink *characterLink = &characterLinks[i];
        if (characterLink->value == 0) continue;
        const DisableMovement *disableMovement = ecs_get(world, characterLink->value, DisableMovement);
        if (disableMovement->value) continue;
        unsigned char is_toggle_camera = 0;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Mouse)) {
                const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                if (mouse->middle.pressed_this_frame) is_toggle_camera = 1;
            } else if (ecs_has(world, device_entity, Gamepad)) {
                const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                if (gamepad->right_stick_push.pressed_this_frame) is_toggle_camera = 1;
            }
        }
        if (is_toggle_camera) zoxel_log("   > toggling camera state  [%lu]\n", characterLink->value);
        if (is_toggle_camera) toggle_camera_perspective(world, characterLink->value);
    }
} zox_declare_system(PlayerToggleCameraSystem)