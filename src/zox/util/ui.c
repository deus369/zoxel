
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
    SDL_ShowCursor(SDL_DISABLE);
    const ecs_entity_t texture_source = string_hashmap_get(files_hashmap_textures, new_string_data("cursor_01"));
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
