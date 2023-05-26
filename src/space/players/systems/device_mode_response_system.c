ecs_entity_t get_first_ui(ecs_world_t *world) {
    ecs_entity_t first_ui = 0;
    if (ecs_is_alive(world, main_menu)) {
        const Children *ui_children = ecs_get(world, main_menu, Children);
        first_ui = ui_children->value[1];
    } else if (ecs_is_alive(world, pause_ui)) {
        const Children *ui_children = ecs_get(world, pause_ui, Children);
        first_ui = ui_children->value[1];
    }
    return first_ui;
}

void DeviceModeResponseSystem(ecs_iter_t *it) {
    // if (!ecs_query_changed(NULL, it)) return;
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 1);
    const DeviceModeDirty *deviceModeDirtys = ecs_field(it, DeviceModeDirty, 2);
    for (int i = 0; i < it->count; i++) {
        const DeviceMode *deviceMode = &deviceModes[i];
        const DeviceModeDirty *deviceModeDirty = &deviceModeDirtys[i];
        if (deviceModeDirty->value != 0 && deviceModeDirty->value != deviceMode->value) {
            // zoxel_log("     > devicemode response [%i -> %i]\n", deviceModeDirty->value, deviceMode->value);
            if (deviceModeDirty->value == zox_device_mode_gamepad) {
                // select main menu ui - also set player selected ui target
                ecs_entity_t first_ui = get_first_ui(it->world);
                raycaster_select_ui_mut(it->world, main_player, first_ui);
            } else if (deviceModeDirty->value == zox_device_mode_keyboardmouse) {
                raycaster_select_ui_mut(it->world, main_player, 0);
            }
        }
    }
}
zox_declare_system(DeviceModeResponseSystem)

// if (!ecs_query_changed(it->ctx, NULL)) return;