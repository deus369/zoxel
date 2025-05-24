float delay_terrain_time = 0.54f;
float delay_terrain_time2 = 0.64f;

void post_player_start_game(ecs_world_t *world, const ecs_entity_t player) {
#ifdef zox_disable_player_ui
    return;
#endif
    // do this in post? spawn all at once! after loaded character
    spawn_in_game_ui(world, player); //  character_group);
    // also spawn canvas
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuActions, menu_actions)
    if (!menu_actions) {
        spawn_player_menu_actions(world, player);
    }
}

// called on spawn terrain event
void spawn_vox_player_character_in_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data(player_vox_model));
    if (!vox) {
        zox_log(" ! [tall_cube] not found on player\n")
    }
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera) return;
    const ecs_entity_t game = zox_get_value(player, GameLink)
    if (!game) return;
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    if (!realm) return;
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    if (!terrain) return;
    byte is_new_game = 1;
#ifndef zox_disable_save_games
    is_new_game = !has_save_game_file(game_name, "player.dat");
#endif
    float3 spawn_position;
    float4 spawn_rotation;
    ecs_entity_t chunk = 0;
    if (is_new_game) {
        spawn_rotation = quaternion_identity;
        const ChunkLinks *chunk_links = zox_get(terrain, ChunkLinks)
        int3 chunk_position = int3_zero;
        byte3 local_position = byte3_zero;
        const ChunkOctree *chunk_above = NULL;
        byte found_position = 0;
        for (int i = 6; i >= -6; i--) {
            chunk_position.y = i;
            chunk = int3_hashmap_get(chunk_links->value, chunk_position);
            if (!chunk) {
                // zox_log("> no chunk here [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z)
                continue;
            }
            // zox_log("+ terrain chunk at: %i\n", i)
            zox_geter(chunk, ChunkOctree, chunkd)
            local_position = find_position_on_ground(chunkd, chunkd->max_depth, chunk_above, 1);
            if (!byte3_equals(byte3_full, local_position)) {
                found_position = 1;
                break;
            }
            chunk_above = chunkd;
        }
        // if (found_position) zox_log(" + found player position: chunk_position %ix%ix%i - local_position %ix%ix%i\n", chunk_position.x, chunk_position.y, chunk_position.z, local_position.x, local_position.y, local_position.z)
        if (!found_position) {
            zox_log(" ! failed finding spawn position for player\n")
        }
        const byte depth = chunk_above != NULL ? chunk_above->max_depth : 0;
        const int3 chunk_dimensions = (int3) { powers_of_two[depth], powers_of_two[depth], powers_of_two[depth] };

        const int3 chunk_voxel_position = get_chunk_voxel_position(chunk_position, chunk_dimensions);
        spawn_position = local_to_real_position_character(local_position, chunk_voxel_position, (float3) { 0.5f, 1.0f, 0.5f }, depth);
    } else {
        // get character position/rotation
        load_character_p(&spawn_position, &spawn_rotation);
    }

    spawn_character3D_data spawn_data = {
        .player = player,
        .vox = vox,
        .terrain = terrain,
        .position = spawn_position,
        .rotation = spawn_rotation,
    };
    const ecs_entity_t e = spawn_character3D_player(world, spawn_data);
    // zox_log("+ player character spawned [%lu]\n", character)
    zox_set(e, ChunkLink, { chunk })
    zox_set(player, CharacterLink, { e })
    zox_set(e, PlayerLink, { player })
    zox_set(e, CameraLink, { camera })
    attach_camera_to_character(world, player, camera, e);
#ifndef zox_disable_save_games
    if (!is_new_game) {
        delay_event(world, &load_player_e, player, 0.01f);
    } else {
        delay_event(world, &save_player_e, player, 0.01f);
    }
#endif
    delay_event(world, &post_player_start_game, player, 0.1);
}

void on_spawned_terrain(ecs_world_t *world, const ecs_entity_t player) {
    // zox_log("on_spawned_terrain\n")
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    #ifdef zox_disable_player_character
        attach_camera_to_character(world, player, camera, 0);
    #else
        if (game_rule_attach_to_character) {
            spawn_vox_player_character_in_terrain(world, player);
            // delay_event(world, &spawn_vox_player_character_in_terrain, player, 1);

            // delay_event(world, &spawn_vox_player_character_in_terrain, player, delay_terrain_time);
        } else {
            attach_camera_to_character(world, player, camera, 0);
        }
    #endif

    const ecs_entity_t game = zox_get_value(player, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    play_playlist(world, realm, 1);
}

void fix_camera_in_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const byte depth = terrain_depth;
    const int3 chunk_dimensions = (int3) { powers_of_two[depth], powers_of_two[depth], powers_of_two[depth] };
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const float3 position = zox_get_value(camera, Position3D)
    int3 terrain_position = real_position_to_chunk_position(position, chunk_dimensions, terrain_depth);
    const ecs_entity_t game = zox_get_value(player, GameLink)
    if (!game || !zox_has(game, RealmLink)) return;
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    if (!realm || !zox_has(realm, TerrainLink)) return;
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    if (!terrain) return;
    zox_set(camera, StreamPoint, { terrain_position })
    zox_set(camera, VoxLink, { terrain })
    // zox_set(camera, TerrainLink, { terrain })
    zox_set(camera, StreamDirty, { zox_general_state_trigger })
    zox_set(terrain, StreamEndEvent, { on_spawned_terrain })
    zox_set(terrain, EventInput, { player }) // todo: make player parent and get children players
    // weirdly when i have second camera, this line will cause destruction of frame buffer:
    // zox_add_tag(camera, Character3D)
    // zox_log(" > camera set stream point [%lu]\n", camera)
}


// spawn character and set camera to streaming terrain
void player_start_game3D_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    float3 spawn_position = (float3) { 8, 8.5f, 8 };
    float4 spawn_rotation = quaternion_identity;
#ifndef zox_disable_save_games
    const byte is_new_game = !has_save_game_file(game_name, "player.dat");
    if (!is_new_game) {
        load_character_p(&spawn_position, &spawn_rotation);
    }
#endif
    zox_set(camera, Position3D, { spawn_position })
    zox_set(camera, Rotation3D, { spawn_rotation })
    delay_event(world, &fix_camera_in_terrain, player, 0.01f);
    // fix_camera_in_terrain(world, player, on_spawned_terrain);
}