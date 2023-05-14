extern void attach_to_character(ecs_world_t *world, ecs_entity_t camera, ecs_entity_t character);
// do I still need render_camera_matrix? - yes - used to insert matrix in each camera system run

ecs_entity_t respawn_camera(ecs_world_t *world) {
    ecs_entity_t old_camera_entity = main_cameras[0];
    float3 camera_position = ecs_get(world, old_camera_entity, Position3D)->value;
    float4 camera_rotation = ecs_get(world, old_camera_entity, Rotation3D)->value;
    int2 camera_screen_dimensions = ecs_get(world, old_camera_entity, ScreenDimensions)->value;
    float4x4 view_matrix = ecs_get(world, old_camera_entity, ViewMatrix)->value;
    // spawn new free roam camera
    ecs_delete(world, old_camera_entity);
    ecs_entity_t e = spawn_free_camera(world, camera_position, camera_rotation, camera_screen_dimensions, (int2) { });
    ecs_set(world, e, ViewMatrix, { view_matrix });
    render_camera_matrix = view_matrix;
    return e;
}

ecs_entity_t respawn_base_camera(ecs_world_t *world) {
    ecs_entity_t old_camera_entity = main_cameras[0];
    float3 camera_position = ecs_get(world, old_camera_entity, Position3D)->value;
    float4 camera_rotation = ecs_get(world, old_camera_entity, Rotation3D)->value;
    int2 camera_screen_dimensions = ecs_get(world, old_camera_entity, ScreenDimensions)->value;
    float4x4 view_matrix = ecs_get(world, old_camera_entity, ViewMatrix)->value;
    // spawn new free roam camera
    ecs_delete(world, old_camera_entity);
    ecs_entity_t e = spawn_base_camera(world, camera_position, camera_rotation, camera_screen_dimensions, (int2) { });
    ecs_set(world, e, ViewMatrix, { view_matrix });
    render_camera_matrix = view_matrix;
    return e;
}

void stop_playing_game(ecs_world_t *world) {
    ecs_set(world, local_game, GameState, { zoxel_game_state_main_menu });
    main_cameras[0] = respawn_base_camera(world);
}

void play_game(ecs_world_t *world) {
    // start game
    ecs_set(world, local_game, GameState, { zoxel_game_state_playing });
    // get previous camera data
    main_cameras[0] = respawn_camera(world);
    ecs_add(world, main_cameras[0], Streamer);
    ecs_add(world, main_cameras[0], StreamPoint);
    ecs_set(world, main_cameras[0], VoxLink, { main_terrain_world });
    // \todo Fix issue with rotation, due to euler setting, make sure to set euler when spawning cameras
    #ifdef zoxel_spawn_character3Ds
        spawn_many_characters3D(world);
    #endif
    #ifdef zoxel_test_single_character3Ds
        spawn_many_characters3D(world);
    #endif
    #ifndef zoxel_disable_attach_on_start
        attach_to_character(world, main_cameras[0], main_character3D);
    #endif
}


void PlayGameSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const GenericEvent *genericEvents = ecs_field(it, GenericEvent, 1);
    for (int i = 0; i < it->count; i++) {
        const GenericEvent *genericEvent = &genericEvents[i];
        if (genericEvent->value == 1) {
            play_game(world);
            // zoxel_log(" > game play begins [%lu]\n", it->entities[i]);
        }
    }
}
zox_declare_system(PlayGameSystem)