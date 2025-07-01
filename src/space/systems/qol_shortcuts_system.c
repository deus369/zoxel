// quality of life - F Keys
void QolShortcutsSystem(ecs_iter_t *it) {
    byte is_toggle_fullscreen = 0;
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device)) {
                continue;
            }
            if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                if (keyboard->f11.pressed_this_frame) {
                    is_toggle_fullscreen = 1;
                    // zox_log(" > toggled fullscreen mode\n")
                } else if (keyboard->f10.pressed_this_frame) {
                    is_render_fog = !is_render_fog;
                    // zox_log(" > set fog [%i]\n", is_render_fog)
                } else if (keyboard->f9.pressed_this_frame) {
                    toggle_free_roam_camera(world, e);
                    // zox_log(" > set camera free roam [%i]\n", camera_mode)
                }
            }
        }
    }
    if (is_toggle_fullscreen) {
        sdl_toggle_fullscreen(world, main_app);
    }
} zox_declare_system(QolShortcutsSystem)