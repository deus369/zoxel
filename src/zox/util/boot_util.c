// #define zox_log_camera_spawning

ecs_entity_t spawn_player_camera(ecs_world_t *world, const ecs_entity_t player, const unsigned char index, const float3 camera_position, const float4 camera_rotation, const int2 viewport_position, const int2 viewport_size, const float4 screen_to_canvas) {
    main_menu_rotation_speed = quaternion_from_euler( (float3) { 0, -main_camera_rotation_speed * degreesToRadians, 0 });
    float fov = get_camera_mode_fov(camera_mode);
    const ecs_entity_t e = spawn_camera_base(world, prefab_camera_game, camera_position, camera_rotation, fov, viewport_position, viewport_size, screen_to_canvas);
#ifdef zox_log_camera_spawning
    zox_log(" + spawned base camera\n")
#endif
    zox_add_tag(e, Camera3D)
    const ecs_entity_t e2 = spawn_camera_ui(world, prefab_camera_ui, viewport_position, viewport_size);
#ifdef zox_log_camera_spawning
    zox_log(" + spawned ui camera\n")
#endif
#ifdef zox_mod_animations
    // zox_set(e, EternalRotation, { main_menu_rotation_speed })
#endif
    zox_set(player, CameraLink, { e })
    main_cameras[index] = e;
    ui_cameras[index] = e2;
    // adds a frame buffer object and render buffer to the camera
#ifndef zox_disable_post_processing
    zox_add_tag(e, RenderCamera)
#ifdef zox_log_camera_spawning
    zox_log(" + spawnubg frame buffer object\n")
#endif
    GLuint fbo = spawn_frame_buffer_object(world, e); // test fbo
    if (fbo) {
        GLuint render_buffer = spawn_render_buffer(world, e, viewport_size); // test fbo
        if (render_buffer) {
            connect_render_buffer_to_fbo(fbo, render_buffer);
        }
    }
#endif
    return e;
}

// todo: spawn unique canvas per viewport, viewports per player
#ifdef zox_mod_ui
ecs_entity_t spawn_default_ui(ecs_world_t *world, const ecs_entity_t ui_camera, const int2 dimensions, const float4 screen_to_canvas) {
    const ecs_entity_t canvas = spawn_canvas(world, prefab_canvas, ui_camera, dimensions, screen_to_canvas);
    spawn_canvas_overlay(world, prefab_canvas_overlay, canvas, dimensions);
    spawn_tooltip(world, prefab_tooltip, canvas);

    // custom cursor
    SDL_ShowCursor(SDL_DISABLE);
    const ecs_entity_t texture_source = string_hashmap_get(files_hashmap_textures, new_string_data("cursor_01"));
    const ecs_entity_t fake_mouse = spawn_icon_mouse_follow_canvas(world, prefab_icon_mouse_follow, canvas, dimensions, max_layers2D - 2, float2_zero, 32);
    zox_set(fake_mouse, RenderDisabled, { 0 })
    zox_set(fake_mouse, GenerateTexture, { zox_generate_texture_none })
    clone_texture_data(world, fake_mouse, texture_source);
    zox_set(fake_mouse, TextureDirty, { 1 })
    zox_set(fake_mouse, MeshAlignment, { zox_mesh_alignment_top_left })
    zox_set(mouse_entity, TextureLink, { fake_mouse })

    const int icon_size = default_icon_size * zox_ui_scale;
    spawn_icon_mouse_follow_canvas(world, prefab_icon_mouse_follow, canvas, dimensions, max_layers2D - 3, float2_half, icon_size);
    return canvas;
}

void zox_spawn_main_menu(ecs_world_t *world, const ecs_entity_t player, const char *game_name, ecs_entity_t canvas) {
    const float2 main_menu_anchor = float2_half;
    const int2 main_menu_position = int2_zero;
    zoxel_main_menu = spawn_main_menu(world, player, canvas, game_name, main_menu_position, main_menu_anchor);
#ifdef zoxel_debug_fps
    fps_display = spawn_fps_display(world, canvas);
#endif
#ifdef zoxel_debug_quads
    quads_label = spawn_quad_count_label(world, canvas);
#endif
    // disable until line2Ds reposition/scale based on canvas
    spawn_canvas_edge_lines(world, canvas, 4, color_black);
}

#endif

void spawn_players_cameras_canvases(ecs_world_t *world, const ecs_entity_t game) {
#if defined(zox_mod_players) && defined(zox_mod_ui)
    zox_prefab_set(prefab_canvas, PlayerLink, { 0 })
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
