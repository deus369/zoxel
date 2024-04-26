// #define test_particles2D
void on_terrain_settings_changed(ecs_world_t *world) {
    if (!local_realm) return;
    const VoxelLinks *voxelLinks = zox_get(local_realm, VoxelLinks)
    for (int k = 0; k < voxelLinks->length; k++) {
        // zoxel_log("     > voxel texture renewed [%i]\n", k);
        ecs_entity_t voxel = voxelLinks->value[k];
        const Textures *textureLinks = zox_get(voxel, Textures)
        zox_set(textureLinks->value[0], GenerateTexture, { 1 })
    }
    if (!local_terrain) return;
    const TilemapLink *tilemapLink = zox_get(local_terrain, TilemapLink)
    zox_set(tilemapLink->value, GenerateTexture, { 1 })
}

void PlayerShortcutsSystem(ecs_iter_t *it) {
    zox_iter_world()
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
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
            }
        }
    }
} zox_declare_system(PlayerShortcutsSystem)

void PlayerShortcutsSingleSystem(ecs_iter_t *it) {
    zox_iter_world()
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                if (keyboard->x.pressed_this_frame) toggle_ui(world, &fps_display, &spawn_fps_display);
                else if (keyboard->l.pressed_this_frame) {
                    const ecs_entity_t character = zox_get_value(it->entities[i], CharacterLink)
                    if (zox_has(character, Aura)) {
                        zox_remove_tag(character, Aura)
                        zox_log(" > removed Aura from character\n")
                    } else {
                        zox_add_tag(character, Aura)
                        zox_log(" > added Aura to character\n")
                    }
                }
                else if (keyboard->j.pressed_this_frame) {
                    zoxel_log(" > spawned new sound\n");
                    spawn_sound_from_file(world, 0);
                }
                else if (keyboard->k.pressed_this_frame) {
                    const int2 position = (int2) { 8, 8 };
                    const int2 size = (int2) { 32 * 8, 32 * 8 };
                    const ecs_entity_t source_texture = files_textures[0];
                    const ecs_entity_t canvas = zox_get_value(it->entities[i], CanvasLink)
                    spawn_texture_element(world, canvas, source_texture, position, size);
                }
#ifndef zox_on_startup_spawn_main_menu
                if (keyboard->g.pressed_this_frame) {
                    const ecs_entity_t canvas = zox_get_value(it->entities[i], CanvasLink)
                    const int edge_buffer = 8 * default_ui_scale;
                    const float2 window_anchor = { 0.0f, 1.0f };
                    const int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
                    spawn_main_menu(world, canvas, game_name, window_position, window_anchor, 0);
                }
#endif
#ifdef test_particles2D
                if (keyboard->f.is_pressed) Particle2DSpawnSystem(world, float2_zero, particleSpawnCount);
#endif
            }
        }
    }
} zox_declare_system(PlayerShortcutsSingleSystem)
