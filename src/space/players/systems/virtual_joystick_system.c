// if player is using touchscreen, and touches, then create the joystick ui in new position
// check if touches an invisible ui area
// #define mouse_has_virtual_joysticks

void VirtualJoystickSystem(ecs_iter_t *it) {
    if (!local_game) return;
    const GameState *gameState = ecs_get(world, local_game, GameState);
    unsigned char is_playing = gameState->value == zoxel_game_state_playing;
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 3);
    // ui links?
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        const DeviceMode *deviceMode = &deviceModes[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (deviceMode->value == zox_device_mode_touchscreen) {
                if (ecs_has(world, device_entity, Touchscreen)) {
                    const Children *zevices = ecs_get(world, device_entity, Children);
                    for (int k = 0; k < zevices->length; k++) {
                        ecs_entity_t zevice_entity = zevices->value[k];
                        if (ecs_has(world, zevice_entity, ZevicePointer)) {
                            const ZevicePointer *zevicePointer = ecs_get(world, zevice_entity, ZevicePointer);
                            if (devices_get_pressed_this_frame(zevicePointer->value)) {
                                const ZevicePointerPosition *zevicePointerPosition = ecs_get(world, zevice_entity, ZevicePointerPosition);
                                // spawn joystick ui
                                // toggle_pause_ui(world, it->entities[i]);
                                if (is_playing) spawn_virtual_joystick(world, zevicePointerPosition->value);
                            } else if (devices_get_released_this_frame(zevicePointer->value)) {
                                // destroy joystick ui
                                // toggle_pause_ui(world, it->entities[i]);
                                zox_delete(virtual_joystick)
                            }
                            break;
                        }
                    }
                }
            }
            #ifdef mouse_has_virtual_joysticks
                else if (deviceMode->value == zox_device_mode_keyboardmouse) {
                    if (ecs_has(world, device_entity, Mouse)) {
                        const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                        if (mouse->left.pressed_this_frame) {
                            zoxel_log(" + spawning virtual joystick ui at %ix%i\n", mouse->position.x, mouse->position.y);
                            if (is_playing) spawn_virtual_joystick(world, mouse->position);
                        } else if (mouse->left.released_this_frame) {
                            zoxel_log(" - deleting virtual joystick ui\n");
                            zox_delete(virtual_joystick)
                        }
                    }
                }
            #endif
        }
    }
} zox_declare_system(VirtualJoystickSystem)