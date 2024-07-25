// #define zoxel_mouse_emulate_touch
// #define zoxel_disable_mouse_lock
void VirtualJoystickSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLink, deviceLinks, 1)
    zox_field_in(RaycasterResult, raycasterResults, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RaycasterResult, raycasterResults, raycasterResult)
        if (raycasterResult->value) continue;   // if raycasted ui, don't process
        // todo: use a DeviceMode for logic flow
        zox_field_i(DeviceLink, deviceLinks, deviceLink)
        const ecs_entity_t player = zox_get_value(deviceLink->value, PlayerLink)
        const unsigned char device_mode = zox_get_value(player, DeviceMode)
        const ecs_entity_t game = zox_get_value(player, GameLink)
        if (!game) return;
        const unsigned char game_state = zox_get_value(game, GameState)
        const unsigned char is_game_state_playing = game_state == zox_game_playing;
        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
        zox_field_e()
        if (zox_has(e, Finger)) {
            const ecs_entity_t virtual_joystick = zox_get_value(e, VirtualZeviceLink)
            handle_touch_drag(world, canvas, e, virtual_joystick, is_game_state_playing);
        }
    }
} zox_declare_system(VirtualJoystickSystem)
        /*
         * zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        const unsigned char game_state = zox_get_value(gameLink->value, GameState)
        const unsigned char is_game_state_playing = game_state == zox_game_playing;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (deviceMode->value == zox_device_mode_touchscreen) {
                if (zox_has(device, Touchscreen)) {
                    zox_geter(device, Children, zevices)  // fingers
                    for (int k = 0; k < zevices->length; k++) {
                        const ecs_entity_t zevice = zevices->value[k];
                        if (zox_has(zevice, Finger)) {
                            const ecs_entity_t virtual_joystick = zox_get_value(zevice, VirtualZeviceLink)
                            handle_touch_drag(world, canvas, zevice, virtual_joystick, is_game_state_playing);
                        }
                    }
                }
            }
#ifdef zoxel_mouse_emulate_touch
            else if (deviceMode->value == zox_device_mode_keyboardmouse) {
                if (zox_has(device_entity, Mouse)) {
                    const Mouse *mouse = zox_get( device_entity, Mouse);
                    if (mouse->left.pressed_this_frame) {
                        delete_virtual_joystick(world, canvas);
                        zox_log(" + spawning virtual joystick ui at %ix%i\n", mouse->position.x, mouse->position.y)
                        if (is_game_state_playing) spawn_virtual_joystick(world, canvas, mouse->position);
                    } else if (mouse->left.released_this_frame) {
                        delete_virtual_joystick(world, canvas);
                    } else if (mouse->left.is_pressed && virtual_joystick != 0) {
                        const PixelPosition *virtual_joystick_position = zox_get(virtual_joystick, PixelPosition)
                        const Children *ui_children = zox_get(virtual_joystick, Children)
                        const int2 delta_position = int2_sub(mouse->position, virtual_joystick_position->value);
                        const ecs_entity_t joystick_pointer = ui_children->value[0];
                        const PixelSize *virtual_joystick_size = zox_get(virtual_joystick, PixelSize);
                        const PixelSize *virtual_joystick_pointer_size = zox_get(joystick_pointer, PixelSize);
                        const int2 size_limits = int2_multiply_float(int2_sub(virtual_joystick_size->value, virtual_joystick_pointer_size->value), 0.5f);
                        PixelPosition *pixel_position = zox_get_mut(world, joystick_pointer, PixelPosition);
                        pixel_position->value.x = delta_position.x;
                        pixel_position->value.y = delta_position.y;
                        int2_limit(&pixel_position->value, size_limits);
                        zox_modified(world, joystick_pointer, PixelPosition);
                        // const float2 input_value = (float2) { pixel_position->value.x / (float) size_limits.x, pixel_position->value.y / (float) size_limits.y };
                        //float add_abs = float_abs(input_value.x) + float_abs(input_value.y);
                        //if (add_abs > 1.0f) float2_divide_p(&input_value, add_abs);
                        zox_log(" > joystick value is [%fx%f]\n", input_value.x, input_value.y)
                    }
                }
            }
#endif
        }
    }*/
