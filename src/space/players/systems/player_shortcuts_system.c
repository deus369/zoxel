unsigned char debug_colliders = 0;

void toggle_collision_debug(ecs_world_t *world) {
    debug_colliders = !debug_colliders;
    ecs_defer_begin(world);
    if (debug_colliders) add_physics_debug(world, prefab_character3D);
    else remove_physics_debug(world, prefab_character3D);
    const ChunkLinks *chunkLinks = ecs_get(world, local_terrain, ChunkLinks);
    // for every chunk, use entity links, add or remove physics debug components
    for (int i = 0; i < chunkLinks->value->size; i++) {
        int3_hash_map_pair* pair = chunkLinks->value->data[i];
        while (pair != NULL) {
            const EntityLinks *entityLinks = ecs_get(world, pair->value, EntityLinks);
            for (int j = 0; j < entityLinks->length; j++) {
                ecs_entity_t character_entity = entityLinks->value[j];
                if (debug_colliders) {
                    add_physics_debug(world, character_entity);
                } else {
                    remove_physics_debug(world, character_entity);
                }
                // zoxel_log(" - character_entity [%lu]\n", character_entity);
            }
            pair = pair->next;
        }
    }
    ecs_defer_end(world);
}

void PlayerShortcutsSingleSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Keyboard)) {
                const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                if (keyboard->v.pressed_this_frame) {
                    toggle_ui(world, &game_debug_label, &spawn_game_debug_label);
                } else if (keyboard->x.pressed_this_frame) {
                    toggle_ui(world, &fps_display, &spawn_fps_display);
                } else if (keyboard->c.pressed_this_frame) {
                    toggle_ui(world, &quads_label, &spawn_quad_count_label);
                } else if (keyboard->z.pressed_this_frame) {
                    toggle_collision_debug(world);
                } else if (keyboard->b.pressed_this_frame) {
                    spawn_zoxel_window(world);
                }
                #ifndef zox_on_startup_spawn_main_menu
                    else if (keyboard->g.pressed_this_frame) {
                        const int edge_buffer = 8 * default_ui_scale;
                        float2 window_anchor = { 0.0f, 1.0f };
                        int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
                        const char *game_name = "zoxel";
                        spawn_main_menu(world, game_name, window_position, window_anchor, 0);
                    }
                #endif
            }
        }
    }
} zox_declare_system(PlayerShortcutsSingleSystem)

void on_terrain_settings_changed(ecs_world_t *world) {
    const VoxelLinks *voxelLinks = ecs_get(world, local_realm, VoxelLinks);
    for (int k = 0; k < voxelLinks->length; k++) {
        // zoxel_log("     > voxel texture renewed [%i]\n", k);
        ecs_entity_t voxel = voxelLinks->value[k];
        const Textures *textureLinks = ecs_get(world, voxel, Textures);
        zox_set_only(textureLinks->value[0], GenerateTexture, { 1 })
    }
    const TilemapLink *tilemapLink = ecs_get(world, local_terrain, TilemapLink);
    zox_set_only(tilemapLink->value, GenerateTexture, { 1 })
}

void PlayerShortcutsSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Keyboard)) {
                const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                if (keyboard->m.pressed_this_frame) {
                    zoxel_log(" > generated new music\n");
                    double music_speed = 0.2 + (rand() % 100) * 0.008;
                    zox_set_only(main_music, MusicSpeed, { music_speed });
                    zox_set_only(main_music, GenerateMusic, { 1 });
                } else if (keyboard->n.pressed_this_frame) {
                    zox_visualize_sounds = !zox_visualize_sounds;
                } else if (keyboard->i.pressed_this_frame) {
                    texture_mode = !texture_mode;
                    zoxel_log("    > texture_mode set [%i]\n", texture_mode);
                    // set all voxels to regenerate textures
                    // set tilemap dirty
                    on_terrain_settings_changed(world);
                } else if (keyboard->o.pressed_this_frame) {
                    terrain_texture_outline_type = !terrain_texture_outline_type;
                    zoxel_log("    > terrain_texture_outline_type set [%i]\n", terrain_texture_outline_type);
                    // set all voxels to regenerate textures
                    // set tilemap dirty
                    on_terrain_settings_changed(world);
                } else if (keyboard->u.pressed_this_frame) {
                    // toggle fog
                    is_render_fog = !is_render_fog;
                    zoxel_log("    > is_render_fog set [%i]\n", is_render_fog);
                } else if (keyboard->y.pressed_this_frame) {
                    // toggle fog
                    unsigned char new_camera_mode = camera_mode + 1;
                    if (new_camera_mode > zox_camera_mode_topdown) new_camera_mode = 0;
                    set_camera_mode(world, new_camera_mode);
                }
            }
        }
    }
} zox_declare_system(PlayerShortcutsSystem)

/*if (ecs_is_valid(world, local_character3D) && ecs_has(world, local_character3D, CameraLink)) {
    const CameraLink *cameraLink = ecs_get(world, local_character3D, CameraLink);
    if (ecs_is_valid(world, cameraLink->value) && cameraLink->value != 0) {
        // zoxel_log(" > switching camera view\n");
        float vox_scale = model_scale * 16;
        const LocalPosition3D *localPosition3D = ecs_get(world, cameraLink->value, LocalPosition3D);
        if (localPosition3D->value.z == vox_scale * 0.5f) {
            zox_set_only(cameraLink->value, LocalPosition3D, {{ 0, vox_scale * 2.2f, - vox_scale * 3.6f }})
            zox_set_only(cameraLink->value, LocalRotation3D, { quaternion_from_euler((float3) { 25, 180 * degreesToRadians, 0 }) })
        } else {
            zox_set_only(cameraLink->value, LocalPosition3D, {{ 0, vox_scale * 0.5f, vox_scale * 0.5f }})
            zox_set_only(cameraLink->value, LocalRotation3D, { quaternion_from_euler((float3) { 0, 180 * degreesToRadians, 0 }) })
        }
    }
}*/