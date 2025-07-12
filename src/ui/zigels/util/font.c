void clear_texture(color* data, const int2 size) {
    int index = 0;
    for (int k = 0; k < size.y; k++) {
        for (int j = 0; j < size.x; j++) {
            data[index] = nothing_font_color;
            index++;
        }
    }
}

void generate_font_texture(
    color* data,
    const int2 size,
    const FontData *font_data,
    const color line_color,
    const color fill_color,
    const byte is_shapes,
    byte fill_thickness,
    byte outline_thickness,
    float2 point_padding)
{
    clear_texture(data, size);
    if (!font_data->length) {
        return;
    }
    if (is_shapes) {
        generate_font_lines(data, size, font_data, line_color, font_point_padding);
        scanline_fill_texture(data, size, nothing_font_color, line_color, fill_color);
        if (outline_thickness) {
            generate_splotches_lines(data, size, font_data, line_color, outline_thickness, font_point_padding);
        }
    } else {
        fill_thickness++;
        generate_splotches_lines(data, size, font_data, line_color, fill_thickness, font_point_padding);
    }
}