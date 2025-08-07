ecs_entity_t spawn_menu_game_stats(
    ecs_world_t *world,
    const ecs_entity_t e,  // menu_game
    const ecs_entity_t player,
    Children *children
) {
    if (!player || !zox_has(player, CharacterLink) || !zox_has(player, CanvasLink)) {
        zox_log_error("! invalid player in [spawn_game_ui_stats]");
        return 0;
    }
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    if (!canvas) {
        zox_log_error("! invalid canvas in [spawn_game_ui_stats]");
        return 0;
    }
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    if (!zox_valid(character) || !zox_has(character, StatLinks)) {
        zox_log_error("! invalid character in [spawn_game_ui_stats]");
        return 0;
    }
    zox_geter(character, StatLinks, stats)

    // stats panel:
    byte panel_layer = 1;
    const float2 panel_anchor = float2_top_left;
    const byte panel_padding = 24;
    int2 panel_size = (int2) { 360, 0 };
    const int2 panel_position = (int2) { 16, -16 };
    FrameTextureData panel_texture = (FrameTextureData) {
        .fill_color = window_fill,
        .outline_color = window_outline,
    };

    const byte bar_layer = 2;
    const float2 bar_anchor = float2_half;
    const int2 bar_size = (int2) { 300, 32 };
    const byte bar_padding = 8;
    const int bars_height = 4 * (bar_size.y + bar_padding) - bar_padding;
    int2 bar_position = (int2) { 0, - bar_size.y / 2 + bars_height / 2 };
    panel_size.y = bars_height + panel_padding * 2;

    ElementSpawn body_data = {
        .canvas = {
            .e = canvas,
            .size = zox_gett_value(canvas, PixelSize),
        },
        .parent = {
            .e = e,
            .position = int2_half(zox_gett_value(canvas, PixelSize)),
            .size = zox_gett_value(canvas, PixelSize)
        },
        .element = {
            .prefab = prefab_body,
            .layer = panel_layer,
            .anchor = panel_anchor,
            .position = panel_position,
            .size = panel_size
        },
        .texture = panel_texture,
    };
    const ecs_entity_t panel = spawn_element(world, &body_data);
    add_to_Children(children, panel);
    Children panel_children = { };

    for (int i = 0; i < stats->length; i++) {
        const ecs_entity_t stat = stats->value[i];
        if (zox_has(stat, StatState) || zox_has(stat, StatLevel)) {
            zox_geter_value(stat, ColorRGB, color_rgb, cvalue);
            const ecs_entity_t statbar = spawn_statbar2(
                world,
                canvas,
                panel,
                player,
                (entity2) {
                    character, stat
                },
                cvalue,
                bar_layer,
                bar_anchor,
                bar_size,
                bar_position
            );
            add_to_Children(&panel_children, statbar);
            bar_position.y -= bar_size.y + bar_padding;
        }
    }
    zox_set_ptr(panel, Children, panel_children);
    return panel;
}
        /*if (!has_created_soul_ui && ) {
        /    has_created_soul_ui = 1;
            zox_geter_value(stat, ColorRGB, color_rgb, c)
            const ecs_entity_t statbar = spawn_statbar2(
                world,
                canvas,
                parent,
                player,
                (entity2) {
                    character,
                    stat
                },
                c,
                j++);
            add_to_Children(&body_children, statbar);
        }*/