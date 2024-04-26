ecs_entity_t get_first_ui(ecs_world_t *world, const ecs_entity_t canvas) {
    ecs_entity_t first_ui = 0;
    const Children *children = zox_get(canvas, Children)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t child = children->value[i];
        if (zox_has(child, MenuMain) || zox_has(child, MenuPaused) || zox_has(child, MenuOptions)) {
            const Children *ui_children = zox_get(child, Children)
            // todo: find first navigationalElement to select
            if (ui_children->length >= 1) first_ui = ui_children->value[1];
        }
    }
    return first_ui;
}

void DeviceModeResponseSystem(ecs_iter_t *it) {
    if (!local_game) return;
    zox_iter_world()
    const unsigned char game_state = zox_get_value(local_game, GameState)
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 1);
    const DeviceModeDirty *deviceModeDirtys = ecs_field(it, DeviceModeDirty, 2);
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        const DeviceMode *deviceMode = &deviceModes[i];
        const DeviceModeDirty *deviceModeDirty = &deviceModeDirtys[i];
        if (deviceModeDirty->value != 0 && deviceModeDirty->value != deviceMode->value) {
            if (deviceMode->value == zox_device_mode_touchscreen) {
                if (game_state == zox_game_playing) dispose_in_game_ui_touch(world);
            }
            if (deviceModeDirty->value == zox_device_mode_gamepad) {
                // select main menu ui - also set player selected ui target
                const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
                const ecs_entity_t first_ui = get_first_ui(world, canvas);
                raycaster_select_ui_mut(world, e, first_ui);
            } else if (deviceModeDirty->value == zox_device_mode_keyboardmouse) {
                raycaster_select_ui_mut(world, e, 0);
            } else if (deviceModeDirty->value == zox_device_mode_touchscreen) {
                const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
                if (game_state == zox_game_playing) spawn_in_game_ui_touch(world, canvas);
            }
        }
    }
} zox_declare_system(DeviceModeResponseSystem)
