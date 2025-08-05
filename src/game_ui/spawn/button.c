ecs_entity_t spawn_button_game(
    ecs_world_t *world,
    const ecs_entity_t canvas,
    const ecs_entity_t parent,
    const int2 canvas_size,
    const int2 position,
    const float2 anchor,
    const byte size,
    const ClickEvent event
) {
    SpawnButton spawnButton = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
        .parent = {
            .e = parent,
            .size = canvas_size
        },
        .element = {
            .prefab = prefab_button,
            .position = position,
            .layer = 6,
            .anchor = anchor
        },
        .zext = {
            .text = " ",
            .font_size = size,
            .font_thickness = 4,
            .font_fill_color = default_font_fill_color,
            .font_outline_color = default_font_outline_color
        },
        .button = {
            .prefab_zext = prefab_zext,
            .fill = button_fill,
            .outline = button_outline,
        }};
    const ecs_entity_t e = spawn_button(world,
        spawnButton.canvas,
        spawnButton.parent,
        spawnButton.element,
        spawnButton.zext,
        spawnButton.button);
    zox_set(e, ClickEvent, { event.value })
    return e;
}
