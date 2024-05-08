// spawns a game ui per player
#ifndef zox_disable_player_character3D
unsigned char game_rule_attach_to_character = 1;
#else
unsigned char game_rule_attach_to_character = 0;
#endif
const unsigned char player_vox_index = 0;

void fix_camera_in_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!zox_has(camera, Streamer)) {
        zox_add_only(camera, Streamer)
        zox_add_only(camera, StreamPoint)
    }
    const Position3D *camera_position3D = zox_get(camera, Position3D)
    int3 terrain_position = int3_zero;
    if (camera_position3D) terrain_position = get_chunk_position(camera_position3D->value, default_chunk_size);
    zox_set(camera, StreamPoint, { terrain_position })
    if (local_terrain) zox_set(camera, VoxLink, { local_terrain })
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

void player_start_game_delayed(ecs_world_t *world, const ecs_entity_t player) {
    fix_camera_in_terrain(world, player);
    spawn_vox_player_character_in_terrain(world, player);
}

// todo: plug this in per game module
void player_start_game(ecs_world_t *world, const ecs_entity_t player) {
    // destroy again - secondary players
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, found_child)
    if (!found_child) return;
    zox_delete(found_child)
    // destroy main menu
    disable_inputs_until_release(world, player, zox_device_mode_none);
    trigger_canvas_fade_transition(world, canvas);
    // spawn character and set camera to streaming terrain
    // todo: delay event to spawn character
    // todo: generic function to delay t this event
    if (zox_game_type == zox_game_mode_3D) {
        delay_event(world, &player_start_game_delayed, player, 1.4f);
    } else if (zox_game_type == zox_game_mode_2D) {
        const ecs_entity_t camera = zox_get_value(player, CameraLink)
        attach_to_character(world, player, camera, 0);  // set camera into game mode
        zox_set(camera, Position3D, { { 0, 0, 1 } })
        zox_set(camera, Rotation3D, { quaternion_from_euler((float3) { 0, 0 * degreesToRadians, 0 }) })
        zox_set(camera, Euler, { { 0, 0 * degreesToRadians, 0 } })
        const ecs_entity_t character = spawn_player_character2D(world, camera);
        zox_set(player, CharacterLink, { character })
        // spawn_many_characters2D(world);
    }
}
