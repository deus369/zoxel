void DeviceModeResponseSystem(ecs_iter_t *it) {
    /*if (!ecs_query_changed(NULL, it)) {
        return;
    }*/
    ecs_entity_t first_navivgation_ui = 0;
    if (ecs_is_alive(it->world, main_menu)) {
        const Children *ui_children = ecs_get(it->world, main_menu, Children);
        first_navivgation_ui = ui_children->value[1];
    } else if (ecs_is_alive(it->world, pause_ui)) {
        const Children *ui_children = ecs_get(it->world, pause_ui, Children);
        first_navivgation_ui = ui_children->value[1];
    }
    if (first_navivgation_ui == 0) {
        return;
    }
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 1);
    for (int i = 0; i < it->count; i++) {
        const DeviceMode *deviceMode = &deviceModes[i];
        if (deviceMode->value == zox_device_mode_gamepad) {
            // select main menu ui
            // also set player selected ui target
            raycaster_select_ui_mut(it->world, mouse_entity, first_navivgation_ui);
        } else if (deviceMode->value == zox_device_mode_keyboardmouse) {
            // ecs_set(it->world, play_button_entity, SelectableState, { 0 });
            raycaster_select_ui_mut(it->world, mouse_entity, 0);
        }
    }
}
zoxel_declare_system(DeviceModeResponseSystem)