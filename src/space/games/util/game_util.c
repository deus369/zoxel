extern void attach_to_character(ecs_world_t *world, ecs_entity_t player, ecs_entity_t camera, ecs_entity_t character);
extern ecs_entity_t main_character3D;
unsigned char game_rule_attach_to_character = 1;
// do I still need render_camera_matrix? - yes - used to insert matrix in each camera system run

void end_game(ecs_world_t *world) {
    zoxel_log(" > game state => [playing] to [main_menu]\n");
    zox_delete(pause_ui)
    const int edge_buffer = 8 * default_ui_scale;
    const char *game_name = "zoxel";
    float2 window_anchor = { 0.0f, 1.0f };
    int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
    spawn_main_menu(world, game_name, window_position, window_anchor, 0);
    zox_set_only(local_game, GameState, { zoxel_game_state_main_menu })
    // main_cameras[0] = respawn_base_camera(world, main_cameras[0]);
    disable_inputs_until_release(world, main_player);
}

void play_game(ecs_world_t *world) {
    zoxel_log(" > game state => [main_menu] to [playing]\n");
    zox_delete(main_menu)   // close main menu
    zox_set_only(local_game, GameState, { zoxel_game_state_playing }) // start game
    // ecs_entity_t new_camera = respawn_camera(world, main_cameras[0]);
    // main_cameras[0] = new_camera;
    ecs_entity_t camera_entity = main_cameras[0];
    zox_set_only(camera_entity, VoxLink, { main_terrain })
    if (!ecs_has(world, camera_entity, Streamer)) {
        zox_add_only(camera_entity, Streamer)
        zox_add_only(camera_entity, StreamPoint)
    }
    // \todo Fix issue with rotation, due to euler setting, make sure to set euler when spawning cameras
    #ifdef zoxel_spawn_character3Ds
        spawn_many_characters3D(world);
    #endif
    #ifdef zoxel_test_single_character3Ds
        spawn_many_characters3D(world);
    #endif
    #if defined(zoxel_include_players)
        if (game_rule_attach_to_character) {
            attach_to_character(world, main_player, main_cameras[0], main_character3D);
        } else {
            attach_to_character(world, main_player, main_cameras[0], 0);
        }
    #endif
    disable_inputs_until_release(world, main_player);
}

/*ecs_entity_t respawn_camera(ecs_world_t *world, ecs_entity_t old_camera_entity) {
    float3 camera_position = ecs_get(world, old_camera_entity, Position3D)->value;
    float4 camera_rotation = ecs_get(world, old_camera_entity, Rotation3D)->value;
    int2 camera_screen_dimensions = ecs_get(world, old_camera_entity, ScreenDimensions)->value;
    float4x4 view_matrix = ecs_get(world, old_camera_entity, ViewMatrix)->value;
    render_camera_matrix = camera_matrix;
    ecs_entity_t e = spawn_free_camera(world, camera_position, camera_rotation, camera_screen_dimensions, (int2) { }); // spawn new free roam camera
    zox_set_only(e, ViewMatrix, { view_matrix })
    zox_delete(old_camera_entity)
    return e;
}

ecs_entity_t respawn_base_camera(ecs_world_t *world, ecs_entity_t old_camera_entity) {
    float3 camera_position = ecs_get(world, old_camera_entity, Position3D)->value;
    float4 camera_rotation = ecs_get(world, old_camera_entity, Rotation3D)->value;
    int2 camera_screen_dimensions = ecs_get(world, old_camera_entity, ScreenDimensions)->value;
    float4x4 view_matrix = ecs_get(world, old_camera_entity, ViewMatrix)->value;
    // render_camera_matrix = camera_matrix;
    ecs_entity_t e = spawn_base_camera(world, camera_position, camera_rotation, camera_screen_dimensions, (int2) { }); // spawn new free roam camera
    zox_set_only(e, ViewMatrix, { view_matrix })
    zox_delete(old_camera_entity)
    return e;
}*/