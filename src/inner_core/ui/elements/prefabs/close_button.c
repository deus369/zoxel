extern void button_event_close_window(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element);

ecs_entity_t spawn_prefab_button_close(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_header")
    zox_add_tag(e, CloseButton)
    zox_prefab_set(e, ClickEvent, { &button_event_close_window })
    return e;
}

ecs_entity_t spawn_close_button(ecs_world_t *world, const ecs_entity_t parent, const ecs_entity_t canvas, const int2 parent_position, const int2 parent_size, const int2 position, const int size, byte2 padding, const unsigned char layer, const int2 canvas_size) {
    const float2 anchor = (float2) { 1, 0.5f };
    SpawnButton spawnButton = {
        .canvas = {
            .e = canvas,
            .size = canvas_size },
        .parent = {
            .e = parent,
            .position = parent_position,
            .size = parent_size },
        .element = {
            .position = position,
            .layer = layer,
            .anchor = anchor },
        .zext = {
            .prefab = prefab_zext,
            .text = "X",
            .font_size = size,
            .font_thickness = 4,
            .padding = padding,
            .font_fill_color = default_font_fill_color,
            .font_outline_color = default_font_outline_color },
        .button = {
            .prefab = prefab_close_button,
            .color = button_color }};
    const ecs_entity_t e = spawn_button(world, &spawnButton);
    return e;
}
