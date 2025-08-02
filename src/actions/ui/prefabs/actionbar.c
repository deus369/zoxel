ecs_entity_t spawn_player_menu_actions(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    SpawnWindowUsers data = get_default_spawn_window_users_data(world,
        prefab_menu_actions,
        character,
        canvas,
        canvas_size);
    // window
    data.element.prefab = prefab_menu_actions;
    data.element.anchor = (float2) { 0.5f, 0 };
    data.element.position = (int2) { 0, 48 };
    data.window.user_links_id = zox_id(ActionLinks);
    // header
    data.header_zext.text = "";
    data.header_zext.font_size = 4;
    // grid
    data.window.grid_size = (byte2) { 8, 1 };
    data.window.grid_padding.x = 12;
    data.window.grid_padding.y = 0;
    data.window.grid_margins.x = 20;
    data.window.grid_margins.y = 8;
    // elements
    data.frame.prefab = prefab_frame_action;
    data.icon.prefab = prefab_icon_action;
    int header_height = data.header_zext.font_size + data.header.margins * 2;
    data.element.size = (int2) {
        data.window.grid_padding.x + (data.window.icon_size + data.window.grid_padding.x) * data.window.grid_size.x + data.window.grid_margins.x * 2,
        data.window.grid_padding.y + (data.window.icon_size + data.window.grid_padding.y) * data.window.grid_size.y + data.window.grid_margins.y * 2 + header_height
    };
    data.frame.texture.fill_color = fill_color_frame_action;
    data.frame.texture.outline_color = outline_color_frame_action;
    FrameTextureData texture = (FrameTextureData) {
        .fill_color = fill_color_actionbar,
        .outline_color = outline_color_actionbar
    };
    return spawn_window_users(world, data, texture);
}