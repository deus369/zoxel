ecs_entity_t spawn_close_button(ecs_world_t *world,
    const ecs_entity_t parent,
    const ecs_entity_t canvas,
    const int2 parent_position,
    const int2 parent_size,
    const int2 position,
    const int size,
    byte2 padding,
    const byte layer,
    const int2 canvas_size)
{
    const float2 anchor = (float2) { 1, 0.5f };
    SpawnButton spawnButton = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
        .parent = {
            .e = parent,
            .position = parent_position,
            .size = parent_size
        },
        .element = {
            .prefab = prefab_close_button,
            .position = position,
            .layer = layer,
            .anchor = anchor
        },
        .zext = {
            .text = "X",
            .font_size = size,
            .font_thickness = 4,
            .padding = padding,
            .font_fill_color = default_font_fill_color,
            .font_outline_color = default_font_outline_color
        },
        .button = {
            .prefab_zext = prefab_zext,
            .fill = close_button_fill,
            .outline = close_button_outline,
        }};
    return spawn_button(world,
        spawnButton.canvas,
        spawnButton.parent,
        spawnButton.element,
        spawnButton.zext,
        spawnButton.button);
}
