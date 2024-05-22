void fix_camera_in_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!zox_has(camera, Streamer)) {
        zox_add_only(camera, Streamer)
        zox_add_only(camera, StreamPoint)
    }
    const Position3D *camera_position3D = zox_get(camera, Position3D)
    int3 terrain_position = int3_zero;
    if (camera_position3D) terrain_position = real_position_to_chunk_position(camera_position3D->value, default_chunk_size);
    zox_set(camera, StreamPoint, { terrain_position })
    if (local_terrain) zox_set(camera, VoxLink, { local_terrain })
    if (local_terrain) zox_set(camera, TerrainLink, { local_terrain })
    // zox_log("camera set [%lu]\n", camera)
}

void spawn_vox_player_character_in_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    ecs_entity_2 character_group;
    if (game_rule_attach_to_character) {
        float3 spawn_position = (float3) { 8, 8, 8 }; // zox_get_value(camera, Position3D)
        // if not first player
        if (player != zox_players[0]) {
            spawn_position.x += rand() % 16;
            spawn_position.z += rand() % 16;
        }
        const float4 spawn_rotation = quaternion_identity;
        const vox_file vox = vox_files[player_vox_index]; // get mr penguin vox
        character_group = spawn_player_character3D_in_world(world, &vox, spawn_position, spawn_rotation, 0, player);
        const ecs_entity_t character = character_group.x;
        zox_set(player, CharacterLink, { character })
        zox_set(character, CameraLink, { camera })
        attach_to_character(world, player, camera, character);
        // zox_add_tag(character_group.x, Aura)
    } else {
        attach_to_character(world, player, camera, 0);
    }
    spawn_in_game_ui(world, player, character_group);
}

// spawn character and set camera to streaming terrain
void player_start_game3D_delayed(ecs_world_t *world, const ecs_entity_t player) {
    fix_camera_in_terrain(world, player);
    spawn_vox_player_character_in_terrain(world, player);
}

void player_start_game2D_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    zox_set(camera, Position3D, { { 0, 0, 1 } })
    zox_set(camera, Rotation3D, { quaternion_from_euler((float3) { 0, 0 * degreesToRadians, 0 }) })
    zox_set(camera, Euler, { { 0, 0 * degreesToRadians, 0 } })
    const ecs_entity_t character = spawn_player_character2D(world, camera);
    zox_set(player, CharacterLink, { character })
    zox_set(camera, CharacterLink, { character })
    zox_set(camera, EternalRotation, { float4_identity })
    zox_add_tag(camera, CameraFollower2D)
}

// todo: plug this in per game module
void player_start_game(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, main_menu)
    if (!main_menu) return;
    zox_delete(main_menu)
    disable_inputs_until_release(world, player, zox_device_mode_none);
    trigger_canvas_fade_transition(world, canvas);
    if (zox_game_type == zox_game_mode_3D) {
        delay_event(world, &player_start_game3D_delayed, player, 1.4f);
    } else if (zox_game_type == zox_game_mode_2D) {
        delay_event(world, &player_start_game2D_delayed, player, 1.4f);
    }
}
