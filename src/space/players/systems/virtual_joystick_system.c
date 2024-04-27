// #define zoxel_mouse_emulate_touch
// #define zoxel_disable_mouse_lock
void VirtualJoystickSystem(ecs_iter_t *it) {
    if (!local_game) return;
    const GameState *gameState = zox_get(local_game, GameState)
    const unsigned char is_playing = gameState->value == zox_game_playing;
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 2)
    zox_field_in(DeviceMode, deviceModes, 3)
    zox_field_in(RaycasterResult, raycasterResults, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(RaycasterResult, raycasterResults, raycasterResult)
        if (raycasterResult->value) continue;   // if raycasted ui, don't process
        zox_field_e()
        const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
        zox_field_i_in(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i_in(DeviceMode, deviceModes, deviceMode)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (deviceMode->value == zox_device_mode_touchscreen) {
                if (zox_has(device_entity, Touchscreen)) {
                    const Children *zevices = zox_get(device_entity, Children)
                    const ecs_entity_t virtual_joystick = zevices->value[fingers_count]; // get linked virtual joystick
                    for (int k = 0; k < zevices->length; k++) {
                        const ecs_entity_t zevice_entity = zevices->value[k];
                        if (zox_has(zevice_entity, ZevicePointer)) {
                            handle_touch_drag(world, canvas, zevice_entity, virtual_joystick, is_playing);
                            break;
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
                        if (is_playing) spawn_virtual_joystick(world, canvas, mouse->position);
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
    }
} zox_declare_system(VirtualJoystickSystem)
