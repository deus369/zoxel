ecs_entity_t spawn_menu_options(
    ecs_world_t *world,
    const ecs_entity_t player,
    const ecs_entity_t canvas,
    const int2 position,
    const float2 anchor)
{
    const byte header_font_size = 80;
    const byte font_size = 42;
    const byte is_close_button = 0;
    const int labels_count = 3;
    const text_group labels[] = { { "volume +" }, { "volume -" }, { "return" } };
    const ClickEvent events[] = { { &button_event_volume_increase }, { &button_event_volume_decrease }, { &button_event_menu_main } };
    const byte layer = 1;
    const ecs_entity_t e = spawn_ui_list(world, prefab_ui_list, canvas, menu_options_header_label, labels_count, labels_count, labels, events, position, anchor, is_close_button, header_font_size, font_size, layer, 0, player);
    zox_add_tag(e, MenuOptions)
    zox_name("menu_options")
    return e;
}
