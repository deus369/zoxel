// #define test_particles2D
// Shortcuts for settings
/*void PlayerShortcutsSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(GameLink, gameLinks, 2)
    for (int i = 0; i < it->count; i++) {
        // zox_field_e()
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i(GameLink, gameLinks, gameLink)
        const ecs_entity_t realm = zox_get_value(gameLink->value, RealmLink)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) continue;
            if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                if (keyboard->m.pressed_this_frame) {
                    zox_log(" > generated new music\n")
                    double music_speed = 0.2 + (rand() % 100) * 0.008;
                    zox_set(local_music, MusicSpeed, { music_speed });
                    zox_set(local_music, GenerateMusic, { 1 });
                } else if (keyboard->n.pressed_this_frame) {
                    texture_mode = !texture_mode;
                    on_terrain_settings_changed(world, realm);
                    zox_log("    > texture_mode set [%i]\n", texture_mode)
                } else if (keyboard->m.pressed_this_frame) {
                    terrain_texture_outline_type = !terrain_texture_outline_type;
                    on_terrain_settings_changed(world, realm); // set all voxels to regenerate textures, set tilemap dirty
                    zox_log("    > terrain_texture_outline_type set [%i]\n", terrain_texture_outline_type)
                }
            }
        }
    }
} zoxd_system(PlayerShortcutsSystem)*/
