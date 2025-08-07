entity spawn_label_background(ecs *world,
    const entity prefab,
    const entity parent,
    const entity canvas,
    int2 pixel_position,
    const float2 anchor,
    const byte2 padding,
    const char* text,
    const byte font_size,
    const byte alignment,
    const byte layer,
    const int2 parent_position,
    const int2 parent_size,
    const color label_font_outline_color,
    const color label_font_fill_color,
    const byte render_disabled)
{
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    SpawnZext zextSpawnData = {
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
            .prefab = prefab,
            .layer = layer,
            .anchor = anchor,
            .position = pixel_position,
            .render_disabled = render_disabled,
        },
        .zext = {
            .font_resolution = 32,
            .text = text,
            .font_size = font_size,
            .font_thickness = 1,
            .font_outline_thickness = 1,
            .alignment = alignment,
            .padding = padding,
            .font_fill_color = label_font_fill_color,
            .font_outline_color = label_font_outline_color
        }
    };
    const entity e = spawn_zext(world, &zextSpawnData);
    zox_name("label_background")
    return e;
}
