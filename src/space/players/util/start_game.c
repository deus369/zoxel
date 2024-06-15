void fix_camera_in_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const float3 camera_position3D = zox_get_value(camera, Position3D)
    int3 terrain_position = real_position_to_chunk_position(camera_position3D, default_chunk_size);
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    zox_set(camera, StreamPoint, { terrain_position })
    zox_set(camera, VoxLink, { terrain })
    zox_set(camera, TerrainLink, { terrain })
    // weirdly when i have second camera, this line will cause destruction of frame buffer:
    // zox_add_tag(camera, Character3D)
    // zox_log(" > camera set stream point [%lu]\n", camera)
}

void spawn_vox_player_character_in_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data("tall_cube"));
    if (!vox) {
        zox_log(" ! [tall_cube] not found on player\n")
        return;
    }
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    const ChunkLinks *chunk_links = zox_get(terrain, ChunkLinks)
    int3 chunk_position = int3_zero;
    byte3 local_position = byte3_zero;
    const ChunkOctree *chunk_octree_above = NULL;
    unsigned char found_position = 0;
    for (int i = 4; i >= -4; i--) {
        chunk_position.y = i;
        const ecs_entity_t chunk = int3_hashmap_get(chunk_links->value, chunk_position);
        const ChunkOctree *chunk_octree = zox_get(chunk, ChunkOctree)
        // local_position = find_position_in_chunk(chunk_octree, max_octree_depth);
        local_position = find_position_in_chunk_with_above(chunk_octree, max_octree_depth, chunk_octree_above);
        if (!byte3_equals(byte3_full, local_position)) {
            found_position = 1;
            break;
        }
        chunk_octree_above = chunk_octree;
    }
    if (found_position) zox_log(" + found player position: chunk_position %ix%ix%i - local_position %ix%ix%i\n", chunk_position.x, chunk_position.y, chunk_position.z, local_position.x, local_position.y, local_position.z)
    else zox_log(" ! failed finding spawn position for player\n")
    const int3 chunk_voxel_position = get_chunk_voxel_position(chunk_position, default_chunk_size);
    float3 position = local_to_real_position_character(local_position, chunk_voxel_position);
    const float4 spawn_rotation = quaternion_identity;
    // const ecs_entity_t vox = files_voxes[player_vox_index]; // get mr penguin vox
    ecs_entity_2 character_group = spawn_player_character3D_in_world(world, vox, position, spawn_rotation, 0, player);
    const ecs_entity_t character = character_group.x;
    zox_set(player, CharacterLink, { character })
    zox_set(character, CameraLink, { camera })
    attach_to_character(world, player, camera, character);
    // zox_add_tag(character_group.x, Aura)
    spawn_in_game_ui(world, player, character_group);
}

// spawn character and set camera to streaming terrain
void player_start_game3D_delayed(ecs_world_t *world, const ecs_entity_t player) {
    fix_camera_in_terrain(world, player);
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const float3 spawn_position = (float3) { 8, 8.5f, 8 };
    zox_set(camera, Position3D, { spawn_position })
    zox_set(camera, Rotation3D, { quaternion_identity })
#ifdef zox_disable_player_character
    attach_to_character(world, player, camera, 0);
#else
    if (game_rule_attach_to_character) {
        delay_event(world, &spawn_vox_player_character_in_terrain, player, 0.1f);
    } else {
        attach_to_character(world, player, camera, 0);
    }
#endif
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
