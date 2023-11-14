ecs_entity_t get_first_ui(ecs_world_t *world) {
    ecs_entity_t first_ui = 0;
    if (ecs_is_alive(world, main_menu)) {
        const Children *ui_children = ecs_get(world, main_menu, Children);
        if (ui_children->length >= 1) first_ui = ui_children->value[1];
    } else if (pause_ui != 0 && ecs_is_alive(world, pause_ui)) {
        const Children *ui_children = ecs_get(world, pause_ui, Children);
        if (ui_children->length >= 1) first_ui = ui_children->value[1];
    }
    return first_ui;
}

void DeviceModeResponseSystem(ecs_iter_t *it) {
    if (!local_game) return;
    ecs_world_t *world = it->world;
    unsigned char game_state = zox_get_value(local_game, GameState)
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 1);
    const DeviceModeDirty *deviceModeDirtys = ecs_field(it, DeviceModeDirty, 2);
    for (int i = 0; i < it->count; i++) {
        const DeviceMode *deviceMode = &deviceModes[i];
        const DeviceModeDirty *deviceModeDirty = &deviceModeDirtys[i];
        if (deviceModeDirty->value != 0 && deviceModeDirty->value != deviceMode->value) {
            // zoxel_log("     > devicemode response [%i -> %i]\n", deviceModeDirty->value, deviceMode->value);
            if (deviceMode->value == zox_device_mode_touchscreen) {
                // zox_logg("  > old device mode was touchscreen\n")
                if (game_state == zoxel_game_state_playing) dispose_in_game_ui_touch(world);
            }
            if (deviceModeDirty->value == zox_device_mode_gamepad) {
                // select main menu ui - also set player selected ui target
                ecs_entity_t first_ui = get_first_ui(world);
                raycaster_select_ui_mut(world, main_player, first_ui);
            } else if (deviceModeDirty->value == zox_device_mode_keyboardmouse) {
                raycaster_select_ui_mut(world, main_player, 0);
            } else if (deviceModeDirty->value == zox_device_mode_touchscreen) {
                if (game_state == zoxel_game_state_playing) spawn_in_game_ui_touch(world);
            }
        }
    }
} zox_declare_system(DeviceModeResponseSystem)
