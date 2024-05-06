int2 get_zigel_position(const unsigned char index, const unsigned char total_length, const unsigned char font_size, const unsigned char text_alignment, const byte2 text_padding) {
    const int2 zigel_size = (int2) { font_size, font_size };
    const int half_size = zigel_size.x * total_length / 2.0f;
    int2 zigel_position = (int2) { (zigel_size.x * index - half_size) + zigel_size.x / 2, 0 };
    // default was centred
    /*if (text_alignment == zox_mesh_alignment_centred) { } else*/
    if (text_alignment == zox_mesh_alignment_right) {
        zigel_position.x -= half_size;
        zigel_position.x -= text_padding.x;
    } else if (text_alignment == zox_mesh_alignment_left) {
        zigel_position.x += half_size;
        zigel_position.x += text_padding.x;
    }
    return zigel_position;
}

// For reusing a zigel, set all positions again to position entire text
void set_zigel_position(ecs_world_t *world, const ecs_entity_t zigel, const unsigned char index, const int font_size, const unsigned char text_alignment, const byte2 text_padding, float2 anchor, unsigned char total_length, const int2 parent_pixel_position_global, const int2 parent_pixel_size, const int2 canvas_size) {
    const int2 pixel_position = get_zigel_position(index, total_length, font_size, text_alignment, text_padding);
    const int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    const float2 position = get_element_position(pixel_position_global, canvas_size);
    zox_set(zigel, Position2D, { position })
    zox_set(zigel, PixelPosition, { pixel_position })
    zox_set(zigel, CanvasPosition, { pixel_position_global })
}

// spawns a text character in a place
ecs_entity_t spawn_zext_zigel(ecs_world_t *world, ZigelSpawnData *data) {
    data->position = get_zigel_position(data->array_index, data->zext.length, data->size.x, data->zext.text_alignment, data->zext.text_padding);
    data->anchor = float2_half;
    return spawn_zigel(world, data);
}
