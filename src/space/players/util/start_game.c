// spawns a game ui per player

#ifndef zox_disable_player_character3D
unsigned char game_rule_attach_to_character = 1;
#else
unsigned char game_rule_attach_to_character = 0;
#endif

void player_start_game(ecs_world_t *world, ecs_entity_t player) {
    disable_inputs_until_release(world, player, zox_device_mode_none);
    // ui control
    ecs_entity_t camera = zox_get_value(player, CameraLink) //  main_cameras[0];
    if (zox_game_type == zox_game_mode_3D) {
        spawn_in_game_ui(world, player);
        if (!zox_has(camera, Streamer)) {
            zox_add_only(camera, Streamer)
            zox_add_only(camera, StreamPoint)
        }
        const Position3D *camera_position3D = zox_get(camera, Position3D)
        int3 terrain_position = int3_zero;
        if (camera_position3D) terrain_position = get_chunk_position(camera_position3D->value, default_chunk_size);
        zox_set(camera, StreamPoint, { terrain_position })
        if (local_terrain) zox_set(camera, VoxLink, { local_terrain })
        if (game_rule_attach_to_character) {
            float3 spawn_position = zox_get_value(camera, Position3D)
            spawn_position.x = 8;
            spawn_position.z = 8;
            float4 spawn_rotation = quaternion_identity;
            const vox_file vox = vox_files[3]; // get mr penguin vox
            local_character3D = spawn_player_character3D_in_world(world, &vox, spawn_position, spawn_rotation, 0);
            zox_add_tag(local_character3D, Aura)
            attach_to_character(world, player, camera, local_character3D);
        } else {
            attach_to_character(world, player, camera, 0);
        }
    } else if (zox_game_type == zox_game_mode_2D) {
        attach_to_character(world, player, camera, 0);  // set camera into game mode
        zox_set(camera, Position3D, { 0, 0, 1 })
        zox_set(camera, Rotation3D, { quaternion_from_euler((float3) { 0, 0 * degreesToRadians, 0 }) })
        zox_set(camera, Euler, { 0, 0 * degreesToRadians, 0 })
        ecs_entity_t character = spawn_player_character2D(world, camera);
        zox_set(player, CharacterLink, { character })
        // spawn_many_characters2D(world);
    }
}
