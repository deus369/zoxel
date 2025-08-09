ecs_entity_t plot_time;
ecs_entity_t plot_time_system;
const float plot_line_thickness = 1.0f;

ecs_entity_t spawn_plot_graph(
    ecs_world_t* world,
    ecs_entity_t canvas,
    ecs_entity_t parent,
    int2 parent_position,
    int2 parent_size,
    ecs_entity_t prefab,
    byte layer,
    int2 size,
    int points_count,
    double start_value,
    color c,
    byte is_label,
    byte label_line
) {
    const int lines_count = record_frames_count;
    const int line_margins = 8;   // x
    const float line_spacing = ( size.x - line_margins * 2 ) / (float) (lines_count - 1);
    const int lines_min_height = 0;
    const int lines_max_height = size.y;
    float2 anchor = float2_half;
    int2 position = int2_zero;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int2 positiong = get_element_pixel_position_global(parent_position, parent_size, position, anchor);
    const float2 positionf = get_element_position(positiong, canvas_size);

    // zox_instance(prefab)
    Children children = (Children) { 0 };
    initialize_Children(&children, lines_count + is_label);
    ecs_entity_t e = spawn_layout2(world,
            prefab,
            canvas,
            parent,
            position,
            size,
            anchor,
            layer,
            parent_position,
            parent_size);

    PlotDataDouble data = (PlotDataDouble) { 0 };
    initialize_PlotDataDouble(&data, points_count);
    for (int i = 0; i < points_count; i++) {
        data.value[i] = start_value;
    }
    zox_set_ptr(e, PlotDataDouble, data);
    zox_set(e, PlotMin, { 0 });
    zox_set(e, PlotMax, { 0 });
    zox_add_tag(e, Plot);

    if (is_label) {
        SpawnZext text_data = {
            .canvas = {
                .e = canvas,
                .size = zox_gett_value(canvas, PixelSize)
            },
            .parent = {
                .e = e,
                .position = parent_position,
                .size = parent_size
            },
            .element = {
                .prefab = prefab_zext,
                .position = (int2) { 0, -28 - label_line * (14 + 4 * 2) },
                .layer = layer,
                .anchor = (float2) { 0, 1.0f },
            },
            .zext = {
                .font_resolution = 64,
                .text = "",
                .font_size = 14,
                .font_thickness = 1,
                .alignment = zox_mesh_alignment_top_left,
                .padding = (byte2) { 16, 4 },
                .font_fill_color = default_font_fill_color,
                .font_outline_color = default_font_outline_color
            }
        };

        const ecs_entity_t e2 = spawn_zext(world, &text_data);
        children.value[0] = e2;
        zox_add_tag(e2, PlotLabel);
    }

    // our plot here
    for (int i = 0; i < lines_count; i++) {
        const int position_x = line_margins + i * line_spacing;
        const int2 start_position = (int2) { position_x, lines_min_height };
        const int2 end_position = (int2) { position_x, lines_max_height };
        const ecs_entity_t e2 = spawn_ui_line2D_v2(world,
            canvas,
            e,
            start_position,
            end_position,
            c,
            plot_line_thickness,
            0,
            positionf,
            position,
            layer);
        zox_set(e2, ChildIndex, { i });
        zox_set(e2, ParentLink, { e });
        zox_add_tag(e2, PlotLine)
        children.value[is_label + i] = e2;
    }
    zox_set_ptr(e, Children, children);
    return e;
}