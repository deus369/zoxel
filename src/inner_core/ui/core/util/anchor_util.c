extern int2 get_line_element_mid_point(ecs_world_t *world, ecs_entity_t e);
extern void set_line_element_real_position2D(ecs_world_t *world, ecs_entity_t e, float2 real_position2D, int2 canvas_size, int2 pixel_position);

void anchor_element_position2D_with_header(int2 *position, const float2 position_anchor, const int2 window_size, const float header_height) {
    position->x += (window_size.x / 2.0f) - window_size.x * position_anchor.x;
    position->y += (window_size.y / 2.0f) - (window_size.y + header_height) * position_anchor.y;
}

void reverse_anchor_element_position2D_with_header(int2 *position, const float2 position_anchor, const int2 window_size, const float header_height) {
    position->x -= (window_size.x / 2.0f) - window_size.x * position_anchor.x;
    position->y -= (window_size.y / 2.0f) - (window_size.y + header_height) * position_anchor.y;
}

void anchor_element_position2D(int2 *position, const float2 position_anchor, const int2 window_size) {
    position->x += (window_size.x / 2.0f) - window_size.x * position_anchor.x;
    position->y += (window_size.y / 2.0f) - window_size.y * position_anchor.y;
}

void anchor_element_size2D(int2 *size, const float2 anchor, const int2 parent_size) {
    size->x = parent_size.x * anchor.x;
    size->y = parent_size.y * anchor.y;
}

void set_element_position(ecs_world_t *world, ecs_entity_t e, int2 parent_pixel_position_global, int2 parent_pixel_size, int2 canvas_size) {
    if (e == 0 || !ecs_is_alive(world, e)) return;
    // get e components
    int2 pixel_position = int2_zero;
    if (zox_has(e, PixelPosition)) pixel_position = zox_get_value(e, PixelPosition)
    else pixel_position = get_line_element_mid_point(world, e);
    float2 anchor = float2_zero;    // should i pass this in from parent?
    if (zox_has(e, Anchor)) anchor = zox_get_value(e, Anchor)
    // calculate pixel and real positions
    int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    float2 position = get_element_position(pixel_position_global, canvas_size);
    // now set variables
    if (zox_has(e, Position2D)) {
        Position2D *position2D = zox_get_mut(e, Position2D)
        position2D->value = position;
        zox_modified(e, Position2D)
    }
    if (zox_has(e, CanvasPosition)) {
        CanvasPosition *canvasPosition = zox_get_mut(e, CanvasPosition)
        canvasPosition->value = pixel_position_global;
        zox_modified(e, CanvasPosition)
    }
    set_line_element_real_position2D(world, e, position, canvas_size, pixel_position);
    if (zox_has(e, Children)) {
        int2 pixel_size = zox_get_value(e, PixelSize)
        const Children *children = zox_get(e, Children)
        for (int i = 0; i < children->length; i++) set_element_position(world, children->value[i], pixel_position_global, pixel_size, canvas_size);
    }
}
