// #define zoxel_mouse_emulate_touch
// #define zoxel_disable_mouse_lock
void VirtualJoystickSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(DeviceLink, deviceLinks, 1)
    zox_field_in(RaycasterResult, raycasterResults, 2)
    zox_field_in(ZevicePointer, zevicePointers, 3)
    zox_field_in(VirtualZeviceLink, virtualZeviceLinks, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DeviceLink, deviceLinks, deviceLink)
        if (!deviceLink->value) continue;
        zox_field_i(ZevicePointer, zevicePointers, zevicePointer)
        zox_field_i(VirtualZeviceLink, virtualZeviceLinks, virtualZeviceLink)
        // if (raycasterResult->value) continue;   // if raycasted ui, don't process
        // todo: use a DeviceMode for logic flow
        const ecs_entity_t player = zox_get_value(deviceLink->value, PlayerLink)
        if (!player) continue;
        // const byte device_mode = zox_get_value(player, DeviceMode)
        const ecs_entity_t game = zox_get_value(player, GameLink)
        if (!game) return;
        const byte game_state = zox_get_value(game, GameState)
        const byte is_game_state_playing = game_state == zox_game_playing;
        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
        zox_field_e()
        zox_field_i(RaycasterResult, raycasterResults, raycasterResult)
        if (zox_has(e, Finger)) {
            // if going to spawn a new one, continue
            const byte click_value = zevicePointer->value;
            if (devices_get_pressed_this_frame(click_value) && raycasterResult->value) continue;
            const ecs_entity_t virtual_joystick = virtualZeviceLink->value;
            handle_touch_drag(world, canvas, e, virtual_joystick, is_game_state_playing);
        }
    }
} zox_declare_system(VirtualJoystickSystem)

