// #define zoxel_mouse_emulate_touch
// #define zoxel_disable_mouse_lock
void VirtualJoystickSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DeviceLink)
    zox_sys_in(RaycasterResult)
    zox_sys_in(ZevicePointer)
    zox_sys_in(VirtualZeviceLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(RaycasterResult, raycasterResult)
        zox_sys_i(DeviceLink, deviceLink)
        zox_sys_i(ZevicePointer, zevicePointer)
        zox_sys_i(VirtualZeviceLink, virtualZeviceLink)
        if (!deviceLink->value || !zox_has(e, Finger)) {
            continue;
        }
        // if (raycasterResult->value) continue;   // if raycasted ui, don't process
        // todo: use a DeviceMode for logic flow
        const ecs_entity_t player = zox_get_value(deviceLink->value, PlayerLink)
        if (!zox_valid(player)) {
            continue;
        }
        // const byte device_mode = zox_get_value(player, DeviceMode)
        const ecs_entity_t game = zox_get_value(player, GameLink)
        if (!zox_valid(game)) {
            return;
        }
        const byte game_state = zox_get_value(game, GameState)
        const byte is_game_state_playing = game_state == zox_game_playing;
        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
        // if going to spawn a new one, continue
        const byte click_value = zevicePointer->value;
        if (devices_get_pressed_this_frame(click_value) && raycasterResult->value) {
            continue;
        }
        const ecs_entity_t virtual_joystick = virtualZeviceLink->value;
        handle_touch_drag(world, canvas, e, virtual_joystick, is_game_state_playing);
    }
} zox_declare_system(VirtualJoystickSystem)

