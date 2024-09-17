float delay_terrain_time = 0.54f;
float delay_terrain_time2 = 0.64f;

void post_player_start_game(ecs_world_t *world, const ecs_entity_t player) {
#ifdef zox_disable_player_ui
    return;
#endif
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuActions, menu_actions)
    if (!menu_actions) spawn_menu_actions_player(world, player);
}

void fix_camera_in_terrain(ecs_world_t *world, const ecs_entity_t player) { // , const float3 position) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const float3 position = zox_get_value(camera, Position3D)
    int3 terrain_position = real_position_to_chunk_position(position, default_chunk_size);
    const ecs_entity_t game = zox_get_value(player, GameLink)
    if (!game || !zox_has(game, RealmLink)) return;
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    if (!realm || !zox_has(realm, TerrainLink)) return;
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    if (!terrain) return;
    zox_set(camera, StreamPoint, { terrain_position })
    zox_set(camera, VoxLink, { terrain })
    zox_set(camera, TerrainLink, { terrain })

    zox_set(terrain, StreamDirty, { 1 })
    // weirdly when i have second camera, this line will cause destruction of frame buffer:
    // zox_add_tag(camera, Character3D)
    // zox_log(" > camera set stream point [%lu]\n", camera)
}

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
    unsigned char is_new_game = 1;
#ifndef zox_disable_save_games
    is_new_game = !has_save_game_file(game_name, "player.dat");
#endif
    float3 spawn_position;
    float4 spawn_rotation;
    if (is_new_game) {
        spawn_rotation = quaternion_identity;
        const ChunkLinks *chunk_links = zox_get(terrain, ChunkLinks)
        int3 chunk_position = int3_zero;
        byte3 local_position = byte3_zero;
        const ChunkOctree *chunk_octree_above = NULL;
        unsigned char found_position = 0;
        for (int i = 4; i >= -4; i--) {
            chunk_position.y = i;
            const ecs_entity_t chunk = int3_hashmap_get(chunk_links->value, chunk_position);
            if (!chunk) {
                // zox_log(" > no chunk here [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z)
                continue;
            }
            zox_geter(chunk, ChunkOctree, chunk_octree)
            // local_position = find_position_in_chunk(chunk_octree, max_octree_depth);
            local_position = find_position_in_chunk_with_above(chunk_octree, max_octree_depth, chunk_octree_above);
            if (!byte3_equals(byte3_full, local_position)) {
                found_position = 1;
                break;
            }
            chunk_octree_above = chunk_octree;
        }
        // if (found_position) zox_log(" + found player position: chunk_position %ix%ix%i - local_position %ix%ix%i\n", chunk_position.x, chunk_position.y, chunk_position.z, local_position.x, local_position.y, local_position.z)
        if (!found_position) zox_log(" ! failed finding spawn position for player\n")
        const int3 chunk_voxel_position = get_chunk_voxel_position(chunk_position, default_chunk_size);
        spawn_position = local_to_real_position_character(local_position, chunk_voxel_position, (float3) { 0.5f, 1.0f, 0.5f });
    } else {
        // get character position/rotation
        load_character_p(&spawn_position, &spawn_rotation);
    }
    ecs_entity_2 character_group = spawn_player_character3D_in_world(world, vox, spawn_position, spawn_rotation, 0, player);
    const ecs_entity_t character = character_group.x;
    zox_set(player, CharacterLink, { character })
    zox_set(character, PlayerLink, { player })
    zox_set(character, CameraLink, { camera })
    attach_camera_to_character(world, player, camera, character);
    // zox_add_tag(character_group.x, Aura)
    spawn_in_game_ui(world, player, character_group);
#ifndef zox_disable_save_games
    if (!is_new_game) {
        delay_event(world, &load_player_e, player, 0.01f);
    } else {
        delay_event(world, &save_player_e, player, 0.01f);
    }
#endif
}

// spawn character and set camera to streaming terrain
void player_start_game3D_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    float3 spawn_position = (float3) { 8, 8.5f, 8 };
    float4 spawn_rotation = quaternion_identity;
#ifndef zox_disable_save_games
    const unsigned char is_new_game = !has_save_game_file(game_name, "player.dat");
    if (!is_new_game) {
        load_character_p(&spawn_position, &spawn_rotation);
    }
#endif
    zox_set(camera, Position3D, { spawn_position })
    zox_set(camera, Rotation3D, { spawn_rotation })
    delay_event(world, &fix_camera_in_terrain, player, 0.01f);
    // fix_camera_in_terrain(world, player, spawn_position);
#ifdef zox_disable_player_character
    attach_camera_to_character(world, player, camera, 0);
#else
    if (game_rule_attach_to_character) {
        delay_event(world, &spawn_vox_player_character_in_terrain, player, delay_terrain_time);
    } else {
        attach_camera_to_character(world, player, camera, 0);
    }
#endif
    delay_event(world, &post_player_start_game, player, delay_terrain_time2);
}
