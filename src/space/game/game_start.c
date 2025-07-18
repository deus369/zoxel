// event called when terrain spawned
void on_spawned_terrain(ecs_world_t *world, const ecs_entity_t player) {
    zox_geter_value(player, CharacterLink, ecs_entity_t, character)
    zox_set(character, DisableGravity, { 0 })
    zox_set(character, DisableMovement, { 0 })
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    play_playlist(world, realm, 1);
}

// this connects to terrain end stream event and triggers streaming
void link_camera_to_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const byte depth = terrain_depth;
    const int3 chunk_dimensions = (int3) { powers_of_two[depth], powers_of_two[depth], powers_of_two[depth] };
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const float3 position = zox_get_value(camera, Position3D)
    int3 terrain_position = real_position_to_chunk_position(position, chunk_dimensions, terrain_depth);
    const ecs_entity_t game = zox_get_value(player, GameLink)
    if (!game || !zox_has(game, RealmLink)) {
        return;
    }
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    if (!realm || !zox_has(realm, TerrainLink)) {
        return;
    }
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    if (!terrain) {
        return;
    }

    // if character
    if (game_rule_attach_to_character) {
        byte is_new_game = 1;
#ifndef zox_disable_save_games
        is_new_game = !has_save_game_file(game_name, "player.dat");
#endif
        ecs_entity_t character;
        if (!is_new_game) {
            character = game_start_player_load(world, player);
            delay_event(world, &load_player_e, player, 0.5f);
        } else {
            character = game_start_player_new(world, player);
        }
        delay_event(world, &spawn_player_game_ui, player, 0.01);
        //zox_set(character, DisableGravity, { 1 })
        //zox_set(character, DisableMovement, { 1 })
    } else {
        set_camera_free(world, camera, 1);
    }

    zox_set(camera, StreamPoint, { terrain_position })
    zox_set(camera, VoxLink, { terrain })
    zox_set(camera, StreamDirty, { zox_general_state_trigger })
    zox_set(terrain, EventInput, { player })
    zox_set(terrain, StreamEndEvent, { on_spawned_terrain })
    if (is_log_streaming) {
        zox_log("+ terrain spawning started at [%f]", zox_current_time)
    }
}

// spawn character and set camera to streaming terrain
void player_start_game3D(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    float3 spawn_position = (float3) { 8, 8.5f, 8 };
    float3 spawn_euler = float3_zero;
    float4 spawn_rotation = quaternion_identity;
#ifndef zox_disable_save_games
    const byte is_new_game = !has_save_game_file(game_name, "player.dat");
    if (!is_new_game) {
        load_character_p(&spawn_position, &spawn_euler, &spawn_rotation);
    }
#endif
    zox_set(camera, Position3D, { spawn_position })
    zox_set(camera, Euler, { spawn_euler })
    zox_set(camera, Rotation3D, { spawn_rotation })
    delay_event(world, &link_camera_to_terrain, player, 0.01f);
}

void player_start_game(ecs_world_t *world,
    const ecs_entity_t player,
    const byte is_delays)
{
    disable_inputs_until_release(world, player, zox_device_mode_none, 1);
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, main_menu)
    if (main_menu) {
        zox_delete(main_menu)
    }
    if (is_delays) {
        trigger_canvas_fade_transition(world, canvas, start_game_delay_terrain, start_game_delay_terrain2);
    }
    if (zox_game_type == zox_game_mode_3D) {
        if (is_delays) {
            delay_event(world, &player_start_game3D, player, start_game_delay_terrain + 0.2f);
        } else {
            // player_start_game3D(world, player);
            delay_event(world, &player_start_game3D, player, 0.01f);
        }
    } else if (zox_game_type == zox_game_mode_2D) {
        delay_event(world, &player_start_game2D_delayed, player, 1.4f);
    }
}