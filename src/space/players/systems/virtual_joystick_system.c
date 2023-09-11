// if player is using touchscreen, and touches, then create the joystick ui in new position
// check if touches an invisible ui area
// todo: add to players ui links (ElementLinks)
// #define zoxel_mouse_emulate_touch
// #define zoxel_disable_mouse_lock

void delete_virtual_joystick(ecs_world_t *world) {
    if (virtual_joystick) {
        zoxel_log(" - deleting virtual joystick ui\n");
        zox_delete(virtual_joystick)
        virtual_joystick = 0;
    }
}

void handle_touch_drag(ecs_world_t *world, ecs_entity_t zevice_entity, ecs_entity_t linked_virtual_joystick, unsigned char is_playing) {
    const ZevicePointer *zevicePointer = ecs_get(world, zevice_entity, ZevicePointer);
    if (devices_get_pressed_this_frame(zevicePointer->value)) {
        delete_virtual_joystick(world);
        const ZevicePointerPosition *zevicePointerPosition = ecs_get(world, zevice_entity, ZevicePointerPosition);
        if (is_playing) spawn_virtual_joystick(world, zevicePointerPosition->value);
    } else if (devices_get_released_this_frame(zevicePointer->value)) {
        delete_virtual_joystick(world);
        ZeviceStick *zeviceStick = ecs_get_mut(world, linked_virtual_joystick, ZeviceStick);
        zeviceStick->value = float2_zero;
        ecs_modified(world, linked_virtual_joystick, ZeviceStick);
    } else if (devices_get_is_pressed(zevicePointer->value) && virtual_joystick != 0) {
        const ZevicePointerPosition *zevicePointerPosition = ecs_get(world, zevice_entity, ZevicePointerPosition);
        const PixelPosition *virtual_joystick_position = ecs_get(world, virtual_joystick, PixelPosition);
        const Children *ui_children = ecs_get(world, virtual_joystick, Children);
        int2 delta_position = int2_sub(zevicePointerPosition->value, virtual_joystick_position->value);
        ecs_entity_t joystick_pointer = ui_children->value[0];
        const PixelSize *virtual_joystick_size = ecs_get(world, virtual_joystick, PixelSize);
        const PixelSize *virtual_joystick_pointer_size = ecs_get(world, joystick_pointer, PixelSize);
        int2 size_limits = int2_multiply_float(int2_sub(virtual_joystick_size->value, virtual_joystick_pointer_size->value), 0.5f);
        size_limits.x -= 10;
        size_limits.y -= 10;
        PixelPosition *pixel_position = ecs_get_mut(world, joystick_pointer, PixelPosition);
        pixel_position->value.x = delta_position.x;
        pixel_position->value.y = delta_position.y;
        int2_limit(&pixel_position->value, size_limits);
        ecs_modified(world, joystick_pointer, PixelPosition);
        float2 input_value = (float2) { pixel_position->value.x / (float) size_limits.x, pixel_position->value.y / (float) size_limits.y };
        //float add_abs = float_abs(input_value.x) + float_abs(input_value.y);
        //if (add_abs > 1.0f) float2_divide_p(&input_value, add_abs);
        // input_value.x *= 0.98f;
        // input_value.y *= 0.98f;
        //if (add_abs > 1.0f) float2_normalize_p(&input_value);
        //input_value.x *= 0.7f;
        //input_value.y *= 0.7f;
        ZeviceStick *zeviceStick = ecs_get_mut(world, linked_virtual_joystick, ZeviceStick);
        zeviceStick->value = input_value;
        ecs_modified(world, linked_virtual_joystick, ZeviceStick);
    }
}

void VirtualJoystickSystem(ecs_iter_t *it) {
    if (!local_game) return;
    const GameState *gameState = ecs_get(world, local_game, GameState);
    unsigned char is_playing = gameState->value == zoxel_game_state_playing;
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 3);
    const RaycasterResult *raycasterResults = ecs_field(it, RaycasterResult, 4);
    for (int i = 0; i < it->count; i++) {
        const RaycasterResult *raycasterResult = &raycasterResults[i];
        // if (raycasterResult->value) zoxel_log(" > racasterResult is 1\n");
        if (raycasterResult->value) continue;   // if raycasted ui, don't process
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        const DeviceMode *deviceMode = &deviceModes[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (deviceMode->value == zox_device_mode_touchscreen) {
                if (ecs_has(world, device_entity, Touchscreen)) {
                    const Children *zevices = ecs_get(world, device_entity, Children);
                    ecs_entity_t virtual_joystick = zevices->value[fingers_count]; // get linked virtual joystick
                    for (int k = 0; k < zevices->length; k++) {
                        if (k >= fingers_count) continue;
                        ecs_entity_t zevice_entity = zevices->value[k];
                        if (ecs_has(world, zevice_entity, ZevicePointer)) {
                            handle_touch_drag(world, zevice_entity, virtual_joystick, is_playing);
                            break;
                        }
                    }
                }
            }
            #ifdef zoxel_mouse_emulate_touch
                else if (deviceMode->value == zox_device_mode_keyboardmouse) {
                    if (ecs_has(world, device_entity, Mouse)) {
                        const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                        if (mouse->left.pressed_this_frame) {
                            delete_virtual_joystick(world);
                            zoxel_log(" + spawning virtual joystick ui at %ix%i\n", mouse->position.x, mouse->position.y);
                            if (is_playing) spawn_virtual_joystick(world, mouse->position);
                        } else if (mouse->left.released_this_frame) {
                            delete_virtual_joystick(world);
                        } else if (mouse->left.is_pressed && virtual_joystick != 0) {
                            const PixelPosition *virtual_joystick_position = ecs_get(world, virtual_joystick, PixelPosition);
                            const Children *ui_children = ecs_get(world, virtual_joystick, Children);
                            int2 delta_position = int2_sub(mouse->position, virtual_joystick_position->value);
                            ecs_entity_t joystick_pointer = ui_children->value[0];
                            const PixelSize *virtual_joystick_size = ecs_get(world, virtual_joystick, PixelSize);
                            const PixelSize *virtual_joystick_pointer_size = ecs_get(world, joystick_pointer, PixelSize);
                            int2 size_limits = int2_multiply_float(int2_sub(virtual_joystick_size->value, virtual_joystick_pointer_size->value), 0.5f);
                            PixelPosition *pixel_position = ecs_get_mut(world, joystick_pointer, PixelPosition);
                            pixel_position->value.x = delta_position.x;
                            pixel_position->value.y = delta_position.y;
                            int2_limit(&pixel_position->value, size_limits);
                            ecs_modified(world, joystick_pointer, PixelPosition);
                            float2 input_value = (float2) { pixel_position->value.x / (float) size_limits.x, pixel_position->value.y / (float) size_limits.y };
                            //float add_abs = float_abs(input_value.x) + float_abs(input_value.y);
                            //if (add_abs > 1.0f) float2_divide_p(&input_value, add_abs);
                            zoxel_log(" > joystick value is [%fx%f]\n", input_value.x, input_value.y);
                        }
                    }
                }
            #endif
        }
    }
} zox_declare_system(VirtualJoystickSystem)