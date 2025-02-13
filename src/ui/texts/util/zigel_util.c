int get_zext_max_x(const byte *data, const int length) {
    int x = 0;
    int max_x = 0;
    for (int i = 0; i < length; i++) {
        if (data[i] == zox_char_newline) {
            x = 0;
        } else {
            x++;
            if (x > max_x) max_x = x;
        }
    }
    if (x > max_x) max_x = x;
    return max_x;
}

int get_zext_max_y(const byte *data, const int length) {
    int y = 1;
    for (int i = 0; i < length; i++) {
        if (data[i] == zox_char_newline && i != length - 1) y++;
    }
    return y;
}

int get_zext_x(const byte *data, const int length, const int data_index) {
    int x = 0;
    for (int i = 0; i < data_index; i++) {
        if (data[i] == zox_char_newline) x = 0;
        else x++;
    }
    return x;
}

int get_zext_y(const byte *data, const int length, const int data_index) {
    int y = 0;
    for (int i = 0; i < data_index; i++) {
        if (data[i] == zox_char_newline && i != length - 1) y++;
    }
    return y;
}

int calculate_total_zigels(const byte *data, const int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (data[i] != zox_char_newline) count++;
    }
    return count;
}

// from a zigel (child?) index, get the data char code
byte calculate_zigel_index(const byte *data, const int length, const int spawn_index) {
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (data[i] != zox_char_newline) {
            if (j == spawn_index) return data[i];
            j++;
        }
    }
    return 0;
}

// calculates the child index, takes out ascii like new line that have no zigel spawns
int calculate_zigel_data_index(const byte *data, const int length, const int spawn_index) {
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (data[i] != zox_char_newline) {
            if (j == spawn_index) return i;
            j++;
        }
    }
    zox_log(" ! calculate_zigel_data_index: dataindex failed\n")
    return 0;
}

int2 calculate_zext_size(const byte *data, const int length, const byte font_size, const byte2 padding, const byte line_padding) {
    int x = get_zext_max_x(data, length);
    int y = get_zext_max_y(data, length);
    // zox_log("sizey: %i\n", y)
    return (int2) { font_size * x + padding.x * 2, (font_size) * y + (y - 1) * line_padding + padding.y * 2 };
}

int2 calculate_zigel_position(const byte *data, const int length, const int data_index, const byte font_size, const byte text_alignment, const byte2 padding, const byte line_padding) {
    const int x = get_zext_x(data, length, data_index);
    const int y = get_zext_y(data, length, data_index);
    const int2 size = calculate_zext_size(data, length, font_size, padding, line_padding);
    int2 zigel_position = int2_zero;
    // add half zigel size offset
    zigel_position.x += font_size / 2;
    zigel_position.y -= font_size / 2;
    // displace by total text size
    zigel_position.x -= (size.x - padding.x * 2) / 2;
    zigel_position.y += (size.y - padding.y * 2) / 2;
    // now displace by grid position
    zigel_position.x += x * font_size;
    zigel_position.y -= y * (font_size + line_padding);
    // zigel_position.y += size.y / 2;
    if (text_alignment == zox_mesh_alignment_centred) return zigel_position;
    // default was centred
    if (text_alignment == zox_mesh_alignment_right) {
        zigel_position.x -= size.x / 2;
        //zigel_position.x -= padding.x;
    } else if (text_alignment == zox_mesh_alignment_left) {
        zigel_position.x += size.x / 2;
        //zigel_position.x += padding.x;
    } else if (text_alignment == zox_mesh_alignment_top_right) {
        zigel_position.x -= size.x / 2;
        zigel_position.y -= size.y / 2;
    } else if (text_alignment == zox_mesh_alignment_bottom_right) {
        zigel_position.x -= size.x / 2;
        zigel_position.y += size.y / 2;
    } else if (text_alignment == zox_mesh_alignment_top_left) {
        zigel_position.x += size.x / 2;
        zigel_position.y -= size.y / 2;
    } else if (text_alignment == zox_mesh_alignment_bottom_left) {
        zigel_position.x += size.x / 2;
        zigel_position.y += size.y / 2;
    }
    // zox_log(" i[%i] %c - xy [%ix%i] - zig pos %ix%i\n", data_index, convert_to_ascii(zextData->value[data_index]), x, y, zigel_position.x, zigel_position.y)
    return zigel_position;
}

// For reusing a zigel, set all positions again to position entire text
void set_zigel_position(ecs_world_t *world, const ZextData *zextData, const ecs_entity_t e, const int data_index, const int font_size, const byte text_alignment, const byte2 text_padding, float2 anchor, const byte zigels_count, const int2 parent_position, const int2 parent_size, const int2 canvas_size) {
    const int2 pixel_position = calculate_zigel_position(zextData->value, zextData->length, data_index, font_size, text_alignment, text_padding, default_line_padding);
    const int2 global_position = get_element_pixel_position_global(parent_position, parent_size, pixel_position, anchor);
    const float2 real_position = get_element_position(global_position, canvas_size);
    zox_set(e, CanvasPosition, { global_position })
    zox_set(e, PixelPosition, { pixel_position })
    zox_set(e, Position2D, { real_position })
}

// spawns a text character in a place
ecs_entity_t spawn_zext_zigel(ecs_world_t *world, const ZextData *zextData, SpawnZigel *data) {
    data->element.position = calculate_zigel_position(zextData->value, zextData->length, data->zigel.data_index, data->element.size.x, data->zext.text_alignment, data->zext.text_padding, default_line_padding);
    data->element.anchor = float2_half;
    return spawn_zigel(world, data);
}
