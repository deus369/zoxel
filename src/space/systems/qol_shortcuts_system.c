void QolShortcutsSystem(ecs_iter_t *it) {
    byte toggle_fullscreen = 0;
    byte toggle_maximized = 0;
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device) || !zox_has(device, Keyboard)) {
                continue;
            }
            zox_geter(device, Keyboard, keyboard)
            if (keyboard->f11.pressed_this_frame) {
                toggle_fullscreen = 1;
            } else if (keyboard->f10.pressed_this_frame) {
                toggle_maximized = 1;
            } else if (keyboard->f8.pressed_this_frame) {
                is_render_fog = !is_render_fog;
            }
        }
    }
    if (toggle_fullscreen) {
        zox_toggle_fullscreen(world);
    }
    if (toggle_maximized) {
        zox_toggle_maximized(world);
    }
} zox_declare_system(QolShortcutsSystem)