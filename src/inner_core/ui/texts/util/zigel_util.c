unsigned char get_zext_max_x(const ZextData *zextData) {
    unsigned char x = 0;
    unsigned char max_x = 0;
    for (unsigned char i = 0; i < zextData->length; i++) {
        if (zextData->value[i] == zox_char_newline) {
            x = 0;
        } else {
            x++;
            if (x > max_x) max_x = x;
        }
    }
    if (x > max_x) max_x = x;
    return max_x;
}

unsigned char get_zext_max_y(const ZextData *zextData) {
    unsigned char y = 1;
    for (unsigned char i = 0; i < zextData->length; i++) {
        if (zextData->value[i] == zox_char_newline && i != zextData->length - 1) y++;
    }
    return y;
}

unsigned char get_zext_x(const ZextData *zextData, const unsigned char data_index) {
    unsigned char x = 0;
    for (unsigned char i = 0; i < data_index; i++) {
        if (zextData->value[i] == zox_char_newline) x = 0;
        else x++;
    }
    return x;
}

unsigned char get_zext_y(const ZextData *zextData, const unsigned char data_index) {
    unsigned char y = 0;
    for (unsigned char i = 0; i < data_index; i++) {
        if (zextData->value[i] == zox_char_newline && i != zextData->length - 1) y++;
    }
    return y;
}

unsigned char calculate_total_zigels(const ZextData *zextData) {
    unsigned char count = 0;
    for (unsigned char i = 0; i < zextData->length; i++) {
        if (zextData->value[i] != zox_char_newline) count++;
    }
    return count;
}

// from a zigel index, get the data char code
unsigned char calculate_zigel_index(const ZextData *zextData, const unsigned char spawn_index) {
    unsigned char j = 0;
    for (unsigned char i = 0; i < zextData->length; i++) {
        if (zextData->value[i] != zox_char_newline) {
            if (j == spawn_index) return zextData->value[i];
            j++;
        }
    }
    return 0;
}

unsigned char calculate_zigel_data_index(const ZextData *zextData, const unsigned char spawn_index) {
    unsigned char j = 0;
    for (unsigned char i = 0; i < zextData->length; i++) {
        if (zextData->value[i] != zox_char_newline) {
            if (j == spawn_index) return i;
            j++;
        }
    }
    zox_log("!!! dataindex failed to find\n")
    return 0;
}

int2 calculate_zext_size(const ZextData *zextData, const unsigned char font_size, const byte2 padding) {
    unsigned char x = get_zext_max_x(zextData);
    unsigned char y = get_zext_max_y(zextData);
    // zox_log("sizey: %i\n", y)
    return (int2) { font_size * x + padding.x * 2, font_size * y + padding.y * 2 };
}

int2 calculate_zigel_position(const ZextData *zextData, const unsigned char data_index, const unsigned char font_size, const unsigned char text_alignment, const byte2 padding) {
    const unsigned char x = get_zext_x(zextData, data_index);
    const unsigned char y = get_zext_y(zextData, data_index);
    const int2 size = calculate_zext_size(zextData, font_size, padding);
    int2 zigel_position = (int2) { 0, 0 };
    zigel_position.x -= (size.x - padding.x * 2) / 2;
    zigel_position.x += x * font_size;
    zigel_position.x += font_size / 2;
    zigel_position.y += (size.y - padding.y * 2) / 2;
    zigel_position.y -= y * font_size;
    zigel_position.y -= font_size / 2;
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
    }
    // zox_log(" i[%i] %c - xy [%ix%i] - zig pos %ix%i\n", data_index, convert_to_ascii(zextData->value[data_index]), x, y, zigel_position.x, zigel_position.y)
    return zigel_position;
}

// For reusing a zigel, set all positions again to position entire text
void set_zigel_position(ecs_world_t *world, const ZextData *zextData, const ecs_entity_t e, const unsigned char data_index, const int font_size, const unsigned char text_alignment, const byte2 text_padding, float2 anchor, const unsigned char zigels_count, const int2 parent_position, const int2 parent_size, const int2 canvas_size) {
    const int2 pixel_position = calculate_zigel_position(zextData, data_index, font_size, text_alignment, text_padding);
    const int2 global_position = get_element_pixel_position_global(parent_position, parent_size, pixel_position, anchor);
    const float2 real_position = get_element_position(global_position, canvas_size);
    zox_set(e, CanvasPosition, { global_position })
    zox_set(e, PixelPosition, { pixel_position })
    zox_set(e, Position2D, { real_position })
}

// spawns a text character in a place
ecs_entity_t spawn_zext_zigel(ecs_world_t *world, const ZextData *zextData, ZigelSpawnData *data) {
    data->element.position = calculate_zigel_position(zextData, data->data_index, data->element.size.x, data->zext.text_alignment, data->zext.text_padding);
    data->element.anchor = float2_half;
    return spawn_zigel(world, data);
}
