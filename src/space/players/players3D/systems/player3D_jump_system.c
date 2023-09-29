// #define zox_log_jumping
const double jump_timing = 0.21;

void Player3DJumpSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const CharacterLink *characterLinks = ecs_field(it, CharacterLink, 3);
    for (int i = 0; i < it->count; i++) {
        const CharacterLink *characterLink = &characterLinks[i];
        if (characterLink->value == 0) continue;
        const DisableMovement *disableMovement = ecs_get(world, characterLink->value, DisableMovement);
        if (disableMovement->value == 1) continue;
        const Grounded *grounded = ecs_get(world, characterLink->value, Grounded);
        if (grounded->value == 0) continue;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        unsigned char is_jump_triggered = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Keyboard)) {
                const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                if (keyboard->space.pressed_this_frame) is_jump_triggered = 1;
            } else if (ecs_has(world, device_entity, Gamepad)) {
                const Children *zevices = ecs_get(world, device_entity, Children);
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (ecs_has(world, zevice_entity, ZeviceButton)) {
                        const DeviceButtonType *deviceButtonType = ecs_get(world, zevice_entity, DeviceButtonType);
                        if (deviceButtonType->value == zox_device_button_a) {
                            const ZeviceDisabled *zeviceDisabled = ecs_get(world, zevice_entity, ZeviceDisabled);
                            if (zeviceDisabled->value) continue;
                            const ZeviceButton *zeviceButton = ecs_get(world, zevice_entity, ZeviceButton);
                            // if (devices_get_pressed_this_frame(zeviceButton->value)) is_jump_triggered = 1;
                            // if (devices_get_is_pressed(zeviceButton->value)) zoxel_log(" = jump activated [%lu] at %f\n", zevice_entity, zox_current_time);
                            if (devices_get_is_pressed(zeviceButton->value)) is_jump_triggered = 1;
                            break;
                        }
                    }
                }
            }
        }
        if (is_jump_triggered == 0) continue;
        const Jump *jump = ecs_get(world, characterLink->value, Jump);
        // zoxel_log(" > jump was triggered\n");
        if (jump->value == 0) {
            zox_set(characterLink->value, Jump, { jump_timing })
            zox_set(characterLink->value, Grounded, { 0 })
            #ifdef zox_log_jumping
                zoxel_log(" > in air [%lu] again (%f)\n", characterLink->value, zox_current_time);
            #endif
        }
    }
} zox_declare_system(Player3DJumpSystem)

// const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
// if (gamepad->a.pressed_this_frame) is_jump_triggered = 1;