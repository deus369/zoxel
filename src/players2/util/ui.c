// #define zox_log_camera_spawning

// todo: spawn unique canvas per viewport, viewports per player
#ifdef zox_mod_ui

ecs_entity_t spawn_default_ui(ecs_world_t *world, const ecs_entity_t ui_camera, const int2 dimensions, const float4 screen_to_canvas) {
    const ecs_entity_t canvas = spawn_canvas(world, prefab_canvas, ui_camera, dimensions, screen_to_canvas);
    spawn_canvas_overlay(world, prefab_canvas_overlay, canvas, dimensions);
    spawn_tooltip(world, prefab_tooltip, canvas);
    // custom cursor
    ecs_entity_t zevice_follow = 0;
    if (mouse_entity) {
        zox_geter(mouse_entity, Children, zevices)
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
    if (mouse_entity) {
        zox_set(mouse_entity, TextureLink, { fake_mouse })
    }
    return canvas;
}

#endif

void spawn_players_cameras_canvases(ecs_world_t *world, const ecs_entity_t game) {
    #if defined(zox_mod_players) && defined(zox_mod_ui)
    #ifdef zox_mod_players2
        players_playing = spawn_players(world, game);
    #endif
    set_camera_mode_pre_defined(world);
    set_main_cameras((int) players_playing);
    float3 camera_position = float3_zero;
    float4 camera_rotation = quaternion_identity;
    for (int i = 0; i < players_playing; i++) {
        const ecs_entity_t player = zox_players[i];
        set_camera_transform_to_main_menu(&camera_position, &camera_rotation);
        const float4 screen_to_canvas = (float4) { 1 / (float) players_playing, 1, i / (float) players_playing, 0 };
        const int2 viewport_size = screen_to_canvas_size(viewport_dimensions, screen_to_canvas);
        const int2 viewport_position = screen_to_canvas_position(viewport_dimensions, screen_to_canvas);
        const ecs_entity_t camera = spawn_player_camera(world, player, i, camera_position, camera_rotation, viewport_position, viewport_size, screen_to_canvas);
        const ecs_entity_t ui_camera = ui_cameras[i];
        const ecs_entity_t canvas = spawn_default_ui(world, ui_camera, viewport_size, screen_to_canvas);
        zox_canvases[i] = canvas;
        zox_set(player, CanvasLink, { canvas })
        zox_set(canvas, PlayerLink, { player })
        if (i == 0) {
            main_canvas = canvas;
        }
        #ifdef zoxel_start_with_debug_ui
            toggle_ui_with_tag(spawn_game_debug_label, GameDebugLabel)
        #endif
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
    }
    #endif
}

void zox_spawn_main_menu(ecs_world_t *world, const ecs_entity_t player, const char *game_name, ecs_entity_t canvas) {
    const float2 main_menu_anchor = float2_half;
    const int2 main_menu_position = int2_zero;
    // zoxel_main_menu = spawn_main_menu(world, player, canvas, game_name, main_menu_position, main_menu_anchor);
    spawn_main_start(world, prefab_menu_start, player, canvas, game_name, main_menu_position, main_menu_anchor);
    // disable until line2Ds reposition/scale based on canvas
    spawn_canvas_edge_lines(world, canvas, 4, color_black);
}

void spawn_players_start_ui(ecs_world_t *world) {
    for (int i = 0; i < players_playing; i++) {
        const ecs_entity_t player = zox_players[i];
        const ecs_entity_t canvas = zox_canvases[i];
        zox_spawn_main_menu(world, player, game_name, canvas);
    }
}