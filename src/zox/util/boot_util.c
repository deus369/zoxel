// #define zox_log_camera_spawning

void spawn_players_cameras_canvases(ecs_world_t *world, const ecs_entity_t game) {
#if defined(zox_mod_players) && defined(zox_mod_ui)
#ifdef zox_log_camera_spawning
    zox_log(" > spawn_players_cameras_canvases 1\n")
#endif
#ifdef zox_mod_players2
    players_playing = spawn_players(world, game);
#endif
#ifdef zox_log_camera_spawning
    zox_log(" > spawn_players_cameras_canvases 2\n")
#endif
    set_camera_mode_pre_defined(world);
    set_main_cameras((int) players_playing);
    float3 camera_position = float3_zero;
    float4 camera_rotation = quaternion_identity;
#ifdef zox_log_camera_spawning
    zox_log(" > spawn_players_cameras_canvases 3\n")
#endif
    for (int i = 0; i < players_playing; i++) {
        const ecs_entity_t player = zox_players[i];
        set_camera_transform_to_main_menu(&camera_position, &camera_rotation);
#ifdef zox_log_camera_spawning
        zox_log("   - spawn_players_cameras_canvases 0\n")
#endif
        const float4 screen_to_canvas = (float4) { 1 / (float) players_playing, 1, i / (float) players_playing, 0 };
        const int2 viewport_size = screen_to_canvas_size(viewport_dimensions, screen_to_canvas);
        const int2 viewport_position = screen_to_canvas_position(viewport_dimensions, screen_to_canvas);
#ifdef zox_log_camera_spawning
        zox_log("   - spawn_players_cameras_canvases 1\n")
#endif
        const ecs_entity_t camera = spawn_player_camera(world, player, i, camera_position, camera_rotation, viewport_position, viewport_size, screen_to_canvas);
#ifdef zox_log_camera_spawning
        zox_log("   - spawn_players_cameras_canvases 2\n")
#endif
        const ecs_entity_t ui_camera = ui_cameras[i];
        const ecs_entity_t canvas = spawn_default_ui(world, ui_camera, viewport_size, screen_to_canvas);
        // return;
#ifndef zox_disable_post_processing
#ifndef zox_disable_render_texture
#ifdef zox_disable_post_processing_additional_players
        if (i == zox_disable_player_index) {
#endif
            // spawns a render texture ui and links to camera
            spawn_render_texture(world, prefab_render_texture, canvas, viewport_size, camera);
#ifdef zox_disable_post_processing_additional_players
        }
#endif
#endif
#endif
        zox_spawn_main_menu(world, player, game_name, canvas);
#ifdef zox_log_camera_spawning
        zox_log("   - spawn_players_cameras_canvases 3\n")
#endif
        zox_canvases[i] = canvas;
        zox_set(player, CanvasLink, { canvas })
        zox_prefab_set(canvas, PlayerLink, { player })
        if (i == 0) main_canvas = canvas;
#ifdef zoxel_start_with_debug_ui
        toggle_ui_with_tag(spawn_game_debug_label, GameDebugLabel)
        // toggle_ui(world, canvas, &game_debug_label, &spawn_game_debug_label);
#endif
    }
#ifdef zox_log_camera_spawning
    zox_log(" > spawn_players_cameras_canvases 4\n")
#endif
#endif
}
