// Shortcuts just for testing new stuff
void PlayerTestSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(CanvasLink, canvasLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i_in(CanvasLink, canvasLinks, canvasLink)
        const ecs_entity_t canvas = canvasLink->value;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                 if (keyboard->j.pressed_this_frame) {
                    toggle_cameras_updates();
                    spawn_sound_from_file(world, 0);
                } else if (keyboard->n.pressed_this_frame) {
                    zox_visualize_sounds = !zox_visualize_sounds;
                } else if (keyboard->k.pressed_this_frame) {
                    const int2 position = (int2) { 8, 8 };
                    const int2 size = (int2) { 32 * 8, 32 * 8 };
                    const ecs_entity_t source_texture = files_textures[0];
                    spawn_texture_element(world, canvas, source_texture, position, size);
                    spawn_sound_from_file(world, 0);
                }
#ifndef zox_on_startup_spawn_main_menu
                if (keyboard->g.pressed_this_frame) {
                    const ecs_entity_t canvas = zox_get_value(it->entities[i], CanvasLink)
                    const int edge_buffer = 8 * default_ui_scale;
                    const float2 window_anchor = { 0.0f, 1.0f };
                    const int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
                    spawn_main_menu(world, main_player, canvas, game_name, window_position, window_anchor, 0);
                }
#endif
#ifdef test_particles2D
                if (keyboard->f.is_pressed) Particle2DSpawnSystem(world, float2_zero, particleSpawnCount);
#endif
            }
        }
    }
} zox_declare_system(PlayerTestSystem)
