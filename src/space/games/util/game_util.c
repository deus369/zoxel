extern void attach_to_character(ecs_world_t *world, ecs_entity_t player, ecs_entity_t camera, ecs_entity_t character);
extern void button_event_pause_game(ecs_world_t *world, ecs_entity_t trigger_entity);
extern ecs_entity_t main_character3D;
unsigned char game_rule_attach_to_character = 1;
// do I still need render_camera_matrix? - yes - used to insert matrix in each camera system run
ecs_entity_t game_ui = 0;

void dispose_in_game_ui(ecs_world_t *world) {
    if (game_ui) {
        zox_delete(game_ui)
        game_ui = 0;
    }
}

void spawn_in_game_ui(ecs_world_t *world) {    // spawn game uis
    const DeviceMode *deviceMode = ecs_get(world, main_player, DeviceMode);
    unsigned char is_touch = deviceMode->value == zox_device_mode_touchscreen;
    #ifdef zoxel_mouse_emulate_touch
        is_touch = 1;
    #endif
    if (is_touch) {
        const unsigned char pause_button_size = 80;
        const ClickEvent on_pause_ui = (ClickEvent) { &button_event_pause_game };
        game_ui = spawn_button_on_canvas(world, main_canvas, (int2) { pause_button_size, pause_button_size }, (byte2) { 8, 4 }, (color) { 77, 32, 44, 255 }, "x", pause_button_size, float2_zero, on_pause_ui);   
    }
}

extern void detatch_from_character(ecs_world_t *world, ecs_entity_t player, ecs_entity_t camera, ecs_entity_t character);
void end_game(ecs_world_t *world) {
    zoxel_log(" > game state => [playing] to [main_menu]\n");
    zox_delete(pause_ui)
    // detatch character
    ecs_entity_t main_camera = main_cameras[0]; // get player camera link instead
    ecs_entity_t character = 0;
    if (camera_follow_mode == zox_camera_follow_mode_attach) character = ecs_get(world, main_camera, ParentLink)->value;
    else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) character = ecs_get(world, main_camera, CameraFollowLink)->value;
    if (character != 0) detatch_from_character(world, main_player, main_camera, main_character3D);
    const int edge_buffer = 8 * default_ui_scale;
    const char *game_name = "zoxel";
    float2 window_anchor = { 0.0f, 1.0f };
    int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
    spawn_main_menu(world, game_name, window_position, window_anchor, 0);
    zox_set_only(local_game, GameState, { zoxel_game_state_main_menu })
    // main_cameras[0] = respawn_base_camera(world, main_cameras[0]);
    disable_inputs_until_release(world, main_player);
    dispose_in_game_ui(world);
}

void play_game(ecs_world_t *world) {
    zoxel_log(" > game state => [main_menu] to [playing]\n");
    zox_delete(main_menu)   // close main menu
    zox_set_only(local_game, GameState, { zoxel_game_state_playing }) // start game
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
        if (game_rule_attach_to_character) attach_to_character(world, main_player, main_cameras[0], main_character3D);
        else attach_to_character(world, main_player, main_cameras[0], 0);
    #endif
    disable_inputs_until_release(world, main_player);
    spawn_in_game_ui(world);
}

// todo: new hotswap camera function, takes in two camera entities
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