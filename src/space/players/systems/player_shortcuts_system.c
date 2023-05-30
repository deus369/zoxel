unsigned char debug_colliders = 0;

void toggle_collision_debug(ecs_world_t *world) {
    debug_colliders = !debug_colliders;
    ecs_defer_begin(world);
    if (debug_colliders) {
        add_physics_debug(world, prefab_character3D);
    } else {
        remove_physics_debug(world, prefab_character3D);
    }
    const ChunkLinks *chunkLinks = ecs_get(world, main_terrain, ChunkLinks);
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

void PlayerShortcutsSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    for (int i = 0; i < it->count; i++) {
        unsigned char is_toggle_camera = 0;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Keyboard)) {
                const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                if (keyboard->v.pressed_this_frame) {
                    spawn_zoxel_window(world);
                } else if (keyboard->x.pressed_this_frame) {
                    toggle_ui(world, &fps_display, &spawn_fps_display);
                } else if (keyboard->c.pressed_this_frame) {
                    toggle_ui(world, &quads_label, &spawn_quad_count_label);
                } else if (keyboard->z.pressed_this_frame) {
                    toggle_collision_debug(world);
                } else if (keyboard->m.pressed_this_frame) {
                    zoxel_log(" > generated new music\n");
                    double music_speed = 0.2 + (rand() % 100) * 0.008;
                    zox_set_only(main_music, MusicSpeed, { music_speed });
                    zox_set_only(main_music, GenerateMusic, { 1 });
                }
            } else if (ecs_has(world, device_entity, Mouse)) {
                const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                if (mouse->middle.pressed_this_frame) {
                    is_toggle_camera = 1;
                }
            } else if (ecs_has(world, device_entity, Gamepad)) {
                const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                if (gamepad->right_stick_push.pressed_this_frame) {
                    is_toggle_camera = 1;
                }
            }
        }
        if (is_toggle_camera) {
            if (ecs_is_valid(world, main_character3D) && ecs_has(world, main_character3D, CameraLink)) {
                const CameraLink *cameraLink = ecs_get(world, main_character3D, CameraLink);
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
            }
        }
    }
}
zox_declare_system(PlayerShortcutsSystem)