

int2 get_zigel_position(unsigned char index, unsigned char total_length, unsigned char font_size, unsigned char text_alignment, byte2 text_padding) {
    int2 zigel_size = (int2) { font_size, font_size };
    int half_size = zigel_size.x * total_length / 2.0f;
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
void set_zigel_position(ecs_world_t *world, ecs_entity_t zigel, unsigned char index, int font_size,  unsigned char text_alignment, byte2 text_padding, float2 anchor, unsigned char total_length, int2 parent_pixel_position_global, int2 parent_pixel_size, int2 canvas_size) {
    float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    int2 pixel_position = get_zigel_position(index, total_length, font_size, text_alignment, text_padding);

    int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    float2 position = get_element_position(pixel_position_global, canvas_size);
    // float2 position2D = get_ui_real_position2D_parent(position, anchor, parent_pixel_position_global, parent_pixel_size, canvas_size_f, aspect_ratio);
    // int2 global_pixel_position = (int2) { ceil((position2D.x / aspect_ratio + 0.5f) * canvas_size_f.x), ((position2D.y + 0.5f) * canvas_size_f.y) };
    zox_set(zigel, Position2D, { position })
    zox_set(zigel, PixelPosition, { pixel_position })
    zox_set(zigel, CanvasPixelPosition, { pixel_position_global })
}
