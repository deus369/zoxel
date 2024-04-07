// todo: add to players ui links (ElementLinks)
// todo: link each finger pointer to it's own virtual joystick entity
// todo: link each virtual joystick entity to it's own virtual joystick ui
// if player is using touchscreen, and touches, then create the joystick ui in new position
// check if touches an invisible ui area
// #define zoxel_mouse_emulate_touch
// #define zoxel_disable_mouse_lock

void delete_virtual_joystick(ecs_world_t *world) {
    if (virtual_joystick) {
        zox_delete(virtual_joystick)
        virtual_joystick = 0;
    }
}

void handle_touch_drag(ecs_world_t *world, ecs_entity_t zevice_entity, ecs_entity_t linked_virtual_joystick, unsigned char is_playing) {
    const ZevicePointer *zevicePointer = zox_get(zevice_entity, ZevicePointer)
    if (devices_get_pressed_this_frame(zevicePointer->value)) {
        delete_virtual_joystick(world);
        const ZevicePointerPosition *zevicePointerPosition = zox_get(zevice_entity, ZevicePointerPosition)
        if (is_playing) spawn_virtual_joystick(world, zevicePointerPosition->value);
    } else if (devices_get_released_this_frame(zevicePointer->value)) {
        ZeviceStick *zeviceStick = zox_get_mut(linked_virtual_joystick, ZeviceStick)
        zeviceStick->value = float2_zero;
        zox_modified(linked_virtual_joystick, ZeviceStick);
        delete_virtual_joystick(world);
    } else if (devices_get_is_pressed(zevicePointer->value) && virtual_joystick) {
        const ZevicePointerPosition *zevicePointerPosition = zox_get(zevice_entity, ZevicePointerPosition)
        const PixelPosition *virtual_joystick_position = zox_get(virtual_joystick, PixelPosition)
        const Children *ui_children = zox_get(virtual_joystick, Children)
        int2 delta_position = int2_sub(zevicePointerPosition->value, virtual_joystick_position->value);
        ecs_entity_t joystick_pointer = ui_children->value[0];
        const PixelSize *virtual_joystick_size = zox_get(virtual_joystick, PixelSize)
        const PixelSize *virtual_joystick_pointer_size = zox_get(joystick_pointer, PixelSize)
        int2 size_limits = int2_multiply_float(int2_sub(virtual_joystick_size->value, virtual_joystick_pointer_size->value), 0.5f);
        size_limits.x -= 10;
        size_limits.y -= 10;
        PixelPosition *pixel_position = zox_get_mut(joystick_pointer, PixelPosition)
        pixel_position->value.x = delta_position.x;
        pixel_position->value.y = delta_position.y;
        int2_limit(&pixel_position->value, size_limits);
        zox_modified(joystick_pointer, PixelPosition)
        float2 input_value = (float2) { pixel_position->value.x / (float) size_limits.x, pixel_position->value.y / (float) size_limits.y };
        ZeviceStick *zeviceStick = zox_get_mut(linked_virtual_joystick, ZeviceStick);
        zeviceStick->value = input_value;
        zox_modified(linked_virtual_joystick, ZeviceStick)
    }
}

void VirtualJoystickSystem(ecs_iter_t *it) {
    if (!local_game) return;
    const GameState *gameState = zox_get(local_game, GameState)
    unsigned char is_playing = gameState->value == zox_game_playing;
    zox_iter_world()
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 3);
    const RaycasterResult *raycasterResults = ecs_field(it, RaycasterResult, 4);
    for (int i = 0; i < it->count; i++) {
        const RaycasterResult *raycasterResult = &raycasterResults[i];
        if (raycasterResult->value) continue;   // if raycasted ui, don't process
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        const DeviceMode *deviceMode = &deviceModes[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (deviceMode->value == zox_device_mode_touchscreen) {
                if (zox_has(device_entity, Touchscreen)) {
                    const Children *zevices = zox_get(device_entity, Children)
                    ecs_entity_t virtual_joystick = zevices->value[fingers_count]; // get linked virtual joystick
                    for (int k = 0; k < zevices->length; k++) {
                        ecs_entity_t zevice_entity = zevices->value[k];
                        if (zox_has(zevice_entity, ZevicePointer)) {
                            handle_touch_drag(world, zevice_entity, virtual_joystick, is_playing);
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
                        delete_virtual_joystick(world);
                        zox_log(" + spawning virtual joystick ui at %ix%i\n", mouse->position.x, mouse->position.y)
                        if (is_playing) spawn_virtual_joystick(world, mouse->position);
                    } else if (mouse->left.released_this_frame) {
                        delete_virtual_joystick(world);
                    } else if (mouse->left.is_pressed && virtual_joystick != 0) {
                        const PixelPosition *virtual_joystick_position = zox_get(virtual_joystick, PixelPosition)
                        const Children *ui_children = zox_get(virtual_joystick, Children)
                        int2 delta_position = int2_sub(mouse->position, virtual_joystick_position->value);
                        ecs_entity_t joystick_pointer = ui_children->value[0];
                        const PixelSize *virtual_joystick_size = zox_get(virtual_joystick, PixelSize);
                        const PixelSize *virtual_joystick_pointer_size = zox_get(joystick_pointer, PixelSize);
                        int2 size_limits = int2_multiply_float(int2_sub(virtual_joystick_size->value, virtual_joystick_pointer_size->value), 0.5f);
                        PixelPosition *pixel_position = zox_get_mut(world, joystick_pointer, PixelPosition);
                        pixel_position->value.x = delta_position.x;
                        pixel_position->value.y = delta_position.y;
                        int2_limit(&pixel_position->value, size_limits);
                        zox_modified(world, joystick_pointer, PixelPosition);
                        float2 input_value = (float2) { pixel_position->value.x / (float) size_limits.x, pixel_position->value.y / (float) size_limits.y };
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
