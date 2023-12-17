// #define test_particles2D
extern const char *game_name;

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
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                if (keyboard->x.pressed_this_frame) toggle_ui(world, &fps_display, &spawn_fps_display);
                 if (keyboard->j.pressed_this_frame) {
                    zoxel_log(" > spawned new sound\n");
                    spawn_sound_from_file(world, 0);
                 }
#ifndef zox_on_startup_spawn_main_menu
                if (keyboard->g.pressed_this_frame) {
                    const int edge_buffer = 8 * default_ui_scale;
                    float2 window_anchor = { 0.0f, 1.0f };
                    int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
                    // const char *game_name = "zoxel";
                    spawn_main_menu(world, game_name, window_position, window_anchor, 0);
                }
#endif
#ifdef test_particles2D
                if (keyboard->f.is_pressed) Particle2DSpawnSystem(world, float2_zero, particleSpawnCount);
#endif
            }
        }
    }
} zox_declare_system(PlayerShortcutsSingleSystem)

/*if (ecs_is_valid(world, local_character3D) && zox_has(local_character3D, CameraLink)) {
    const CameraLink *cameraLink = zox_get(world, local_character3D, CameraLink);
    if (ecs_is_valid(world, cameraLink->value) && cameraLink->value != 0) {
        // zoxel_log(" > switching camera view\n");
        float vox_scale = model_scale * 16;
        const LocalPosition3D *localPosition3D = zox_get(world, cameraLink->value, LocalPosition3D);
        if (localPosition3D->value.z == vox_scale * 0.5f) {
            zox_set(cameraLink->value, LocalPosition3D, {{ 0, vox_scale * 2.2f, - vox_scale * 3.6f }})
            zox_set(cameraLink->value, LocalRotation3D, { quaternion_from_euler((float3) { 25, 180 * degreesToRadians, 0 }) })
        } else {
            zox_set(cameraLink->value, LocalPosition3D, {{ 0, vox_scale * 0.5f, vox_scale * 0.5f }})
            zox_set(cameraLink->value, LocalRotation3D, { quaternion_from_euler((float3) { 0, 180 * degreesToRadians, 0 }) })
        }
    }
}*/
