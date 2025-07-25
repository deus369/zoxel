// #define zox_log_camera_spawning

// todo: spawn unique canvas per viewport, viewports per player
#ifdef zox_mod_ui

ecs_entity_t spawn_default_ui(ecs_world_t *world,
    const ecs_entity_t ui_camera,
    const int2 dimensions,
    const float4 screen_to_canvas,
    const ecs_entity_t app)
{
    const ecs_entity_t canvas = spawn_canvas(world,
        prefab_canvas,
        ui_camera,
        dimensions,
        screen_to_canvas,
        app);
    spawn_canvas_overlay(world, prefab_canvas_overlay, canvas, dimensions);
    spawn_tooltip(world, prefab_tooltip, canvas);
    // custom cursor
    ecs_entity_t zevice_follow = 0;
    if (local_mouse) {
        zox_geter(local_mouse, Children, zevices)
        zevice_follow = zevices->value[0];
    }
    // SDL_ShowCursor(SDL_DISABLE);
    const ecs_entity_t texture_source = string_hashmap_get(files_hashmap_textures, new_string_data("cursor_01"));
    if (texture_source == 0) {
        zox_log(" ! could not find [cursor_01] mouse texture!\n")
    }
    const ecs_entity_t fake_mouse = spawn_icon_mouse_follow_canvas(world, prefab_icon_mouse_follow, canvas, dimensions, max_layers2D - 2, float2_zero, 32, zevice_follow);
    zox_set(fake_mouse, RenderDisabled, { 0 })
    zox_set(fake_mouse, GenerateTexture, { zox_generate_texture_none })
    clone_texture_data(world, fake_mouse, texture_source);
    zox_set(fake_mouse, TextureDirty, { 1 })
    zox_set(fake_mouse, MeshAlignment, { zox_mesh_alignment_top_left })
    // used for icon mouse pickup
    const int icon_size = default_icon_size * zox_ui_scale;
    icon_mouse_follow = spawn_icon_mouse_follow_canvas(world, prefab_icon_mouse_follow, canvas, dimensions, max_layers2D - 3, float2_half, icon_size, zevice_follow);
    if (local_mouse) {
        zox_set(local_mouse, TextureLink, { fake_mouse })
    }
    return canvas;
}

#endif

void spawn_players_cameras_canvases(ecs_world_t *world,
    const ecs_entity_t game,
    int players_playing,
    const ecs_entity_t app)
{
#if defined(zox_mod_players) && defined(zox_mod_ui)
    set_camera_mode_pre_defined(world, vox_model_scale);
    set_main_cameras((int) players_playing);
    float3 camera_position = float3_zero;
    float4 camera_rotation = quaternion_identity;
    zox_geter_value(app, WindowSize, int2, screen_size)
    CameraLinks cameras = { };
    for (int i = 0; i < players_playing; i++) {
        const ecs_entity_t player = zox_players[i];
        set_camera_transform_to_main_menu(&camera_position, &camera_rotation, terrain_depth);
        const float4 screen_to_canvas = (float4) { 1 / (float) players_playing, 1, i / (float) players_playing, 0 };
        const int2 viewport_size = screen_to_canvas_size(screen_size, screen_to_canvas);
        const int2 viewport_position = screen_to_canvas_position(screen_size, screen_to_canvas);
        const int2 game_viewport_size = scale_viewport(viewport_size);
        const ecs_entity_2 spawned_cameras = spawn_player_camera(world,
            player,
            camera_position,
            camera_rotation,
            screen_to_canvas,
            viewport_position,
            game_viewport_size,
            viewport_size);
        add_to_CameraLinks(&cameras, spawned_cameras.x);
        add_to_CameraLinks(&cameras, spawned_cameras.y);
        const ecs_entity_t canvas = spawn_default_ui(world,
            spawned_cameras.y,
            viewport_size,
            screen_to_canvas,
            app);
        zox_set(player, CanvasLink, { canvas })
        zox_set(canvas, PlayerLink, { player })
        // spawns a render texture ui and links to camera
        create_camera_rbo_and_fbo(world, spawned_cameras.x, game_viewport_size);
        spawn_render_texture(world,
            prefab_render_texture,
            canvas,
            viewport_size,
            game_viewport_size,
            spawned_cameras.x);
        // remove these soon
        zox_canvases[i] = canvas;
        main_cameras[i] = spawned_cameras.x;
        ui_cameras[i] = spawned_cameras.y;
    }
    zox_set_ptr(app, CameraLinks, cameras)
#endif
}

void spawn_players_start_ui(ecs_world_t *world) {
    zox_log_start_game("> spawn_players_start_ui [%i]", players_playing)
    for (int i = 0; i < players_playing; i++) {
        const ecs_entity_t player = zox_players[i];
        const ecs_entity_t canvas = zox_canvases[i];
        zox_log_start_game("    - player [%lu - %s]", player, zox_get_name(player))
        zox_log_start_game("    - canvas [%lu - %s]", canvas, zox_get_name(canvas))
        spawn_main_start(world, prefab_menu_start, player, canvas, game_name);
        // disable until line2Ds reposition/scale based on canvas
        // spawn_canvas_edge_lines(world, canvas, 4, color_black);
    }
}