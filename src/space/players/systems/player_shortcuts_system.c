// #define test_particles2D
void PlayerShortcutsSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i_in(DeviceLinks, deviceLinkss, deviceLinks)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                if (keyboard->m.pressed_this_frame) {
                    zox_logg(" > generated new music\n")
                    double music_speed = 0.2 + (rand() % 100) * 0.008;
                    zox_set(local_music, MusicSpeed, { music_speed });
                    zox_set(local_music, GenerateMusic, { 1 });
                } else if (keyboard->n.pressed_this_frame) {
                    zox_visualize_sounds = !zox_visualize_sounds;
                } else if (keyboard->i.pressed_this_frame) {
                    texture_mode = !texture_mode;
                    zox_log("    > texture_mode set [%i]\n", texture_mode)
                    // set all voxels to regenerate textures
                    // set tilemap dirty
                    on_terrain_settings_changed(world);
                } else if (keyboard->o.pressed_this_frame) {
                    terrain_texture_outline_type = !terrain_texture_outline_type;
                    zox_log("    > terrain_texture_outline_type set [%i]\n", terrain_texture_outline_type)
                    // set all voxels to regenerate textures
                    // set tilemap dirty
                    on_terrain_settings_changed(world);
                } else if (keyboard->u.pressed_this_frame) {
                    // toggle fog
                    is_render_fog = !is_render_fog;
                    zox_log("    > is_render_fog set [%i]\n", is_render_fog)
                } /*else if (keyboard->y.pressed_this_frame) {
                    toggle_camera_mode(world);
                }*/

                else if (keyboard->p.pressed_this_frame) toggle_free_roam_camera(world, e);
            }
        }
    }
} zox_declare_system(PlayerShortcutsSystem)
