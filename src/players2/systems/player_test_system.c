void brain_test_controls(ecs_world_t *world, const Keyboard *keyboard, const ecs_entity_t canvas) {
    if (!local_brain) return;
    if (keyboard->_1.pressed_this_frame) {
        feed_brain_random_input(world, local_brain);
        spawn_sound_from_file(world, prefab_sound, 0);
        zox_log(" + fed brain texture random\n")
    }
    else if (keyboard->_2.pressed_this_frame) {
        if (brain_texture) zox_delete(brain_texture)
        brain_texture = spawn_brain_as_texture(world, local_brain);
        spawn_sound_from_file(world, prefab_sound, 0);
        zox_log(" + spawned brain as texture\n")
    }
    else if (keyboard->_3.pressed_this_frame) {
        if (!brain_texture) return;
        if (brain_texture_ui) zox_delete(brain_texture_ui)
        const int2 position = (int2) { 8, 8 };
        const int2 size = (int2) { 32 * 4, 32 * 4 };
        brain_texture_ui = spawn_element_texture(world, canvas, brain_texture, position, size);
        spawn_sound_from_file(world, prefab_sound, 0);
        zox_log(" + updated brain texture ui\n")
    }
    else if (keyboard->_4.pressed_this_frame) {
        feed_brain_input(world, local_brain, 0.01f);
        spawn_sound_from_file(world, prefab_sound, 0);
        zox_log(" + fed brain empty\n")
    }
    else if (keyboard->_5.pressed_this_frame) {
        zox_log(" + updated brain weights\n")
        randomize_brain_weights(world, local_brain);
        spawn_sound_from_file(world, prefab_sound, 0);
    }
    else if (keyboard->_6.pressed_this_frame) {
        zox_log(" + saved brain texture\n")
        save_brain_as_texture(world, local_brain);
        spawn_sound_from_file(world, prefab_sound, 0);
    }
}

ecs_entity_t tilemap_ui = 0;

void spawn_tilemap_ui(ecs_world_t *world, const Keyboard *keyboard, const ecs_entity_t canvas, const ecs_entity_t realm) {
    const int2 size = (int2) { 320, 320 };
    if (keyboard->_8.pressed_this_frame) {
        if (tilemap_ui) {
            zox_delete(tilemap_ui)
            tilemap_ui = 0;
            return;
        }
        const ecs_entity_t tilemap = zox_get_value(realm, TilemapLink)
        const int2 position = (int2) { 8, 8 };
        tilemap_ui = spawn_element_texture(world, canvas, tilemap, position, size);
        spawn_sound_from_file(world, prefab_sound, 0);
        // zox_log(" + spawned tilemap ui\n")
    }
}

void test_sounds(ecs_world_t *world, const Keyboard *keyboard) {
    /*if (keyboard->_1.pressed_this_frame || keyboard->_2.pressed_this_frame || keyboard->_3.pressed_this_frame || keyboard->_4.pressed_this_frame || keyboard->_5.pressed_this_frame || keyboard->_6.pressed_this_frame || keyboard->_7.pressed_this_frame || keyboard->_8.pressed_this_frame) spawn_sound_from_file(world, prefab_sound, 0);
    */
    /*else if (keyboard->_2.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.6, instrument_piano);
    } else if (keyboard->_3.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.3, instrument_piano_square);
    } else if (keyboard->_4.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.8, instrument_violin);
    } else if (keyboard->_5.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.8, instrument_organ);
    } else if (keyboard->_6.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.8, instrument_edm);
    } else if (keyboard->_7.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.6, instrument_guitar);
    } else if (keyboard->_8.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.8, instrument_flute);
    }*/
}

void test_raycast(ecs_world_t *world, const Keyboard *keyboard, const ecs_entity_t realm, const ecs_entity_t player) {
    /*if (keyboard->_1.pressed_this_frame) set_player_voxel_ray(world, realm, player, 0, 0, 2);
    else if (keyboard->_2.pressed_this_frame) set_player_voxel_ray(world, realm, player, 0, 1, 1);
    else if (keyboard->_3.pressed_this_frame) set_player_voxel_ray(world, realm, player, 0, 3, 1);
    else if (keyboard->_4.pressed_this_frame) set_player_voxel_ray(world, realm, player, 0, 4, 1);
    else if (keyboard->_5.pressed_this_frame) set_player_voxel_ray(world, realm, player, 0, zox_block_dirt_rubble, 1);*/
}

// Shortcuts just for testing new stuff
void PlayerTestSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(CanvasLink, canvasLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        const ecs_entity_t canvas = canvasLink->value;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) continue;
            if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                 if (keyboard->j.pressed_this_frame) {
                    toggle_cameras_updates();
                    spawn_sound_from_file(world, prefab_sound, 0);
                } /*else if (keyboard->n.pressed_this_frame) {
                    zox_visualize_sounds = !zox_visualize_sounds;
                } */ else if (keyboard->h.pressed_this_frame) {
                    const int2 position = (int2) { 8, 8 };
                    const int2 size = (int2) { 32 * 4, 32 * 4 };
                    const ecs_entity_t source_texture = files_textures[2];
                    spawn_element_texture(world, canvas, source_texture, position, size);
                    spawn_sound_from_file(world, prefab_sound, 0);
                }
                test_sounds(world, keyboard);
                // brain_test_controls(world, keyboard, canvas);
                spawn_tilemap_ui(world, keyboard, canvas, local_realm);
                test_raycast(world, keyboard, local_realm, it->entities[i]);
#ifndef zox_on_startup_spawn_main_menu
                if (keyboard->g.pressed_this_frame) {
                    const ecs_entity_t canvas = zox_get_value(it->entities[i], CanvasLink)
                    const int edge_buffer = 8 * zox_ui_scale;
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
