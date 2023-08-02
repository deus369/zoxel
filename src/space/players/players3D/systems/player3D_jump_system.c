const double jump_timing = 0.21;

void Player3DJumpSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const CharacterLink *characterLinks = ecs_field(it, CharacterLink, 3);
    for (int i = 0; i < it->count; i++) {
        const CharacterLink *characterLink = &characterLinks[i];
        if (characterLink->value == 0) continue;
        const Grounded *grounded = ecs_get(world, characterLink->value, Grounded);
        if (grounded->value == 0) return;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        unsigned char is_jump_triggered = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Keyboard)) {
                const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                if (keyboard->space.is_pressed) is_jump_triggered = 1;
            } else if (ecs_has(world, device_entity, Gamepad)) {
                const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                if (gamepad->a.pressed_this_frame) is_jump_triggered = 1;
            }
        }
        if (is_jump_triggered == 0) continue;
        const Jump *jump = ecs_get(world, characterLink->value, Jump);
        // zoxel_log(" > jump was triggered\n");
        if (jump->value == 0) {
            ecs_set(world, characterLink->value, Jump, { jump_timing });
            ecs_set(world, characterLink->value, Grounded, { 0 });
            // zoxel_log(" > in air [%lu] again (%f)\n", characterLink->value, zox_current_time);
        }
    }
} zox_declare_system(Player3DJumpSystem)
