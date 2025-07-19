// todo: refactor this extern
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
    position->x += (window_size.x / 2.0f) - ceil(window_size.x * position_anchor.x);
    position->y += (window_size.y / 2.0f) - ceil(window_size.y * position_anchor.y);
}

void anchor_element_size2D(int2 *size, const float2 anchor, const int2 parent_size) {
    size->x = ceil(parent_size.x * anchor.x);
    size->y = ceil(parent_size.y * anchor.y);
    // zox_log("+ new size [%ix%i] from parent [%ix%i] anchor [%fx%f]", size->x, size->y, parent_size.x, parent_size.y, anchor.x, anchor.y)
}

void set_element_position(ecs_world_t *world,
    const ecs_entity_t e,
    const int2 parent_position,
    const int2 parent_size,
    const int2 canvas_size)
{
    if (!zox_valid(e)) {
        return;
    }
    int2 position = int2_zero;
    if (zox_has(e, PixelPosition)) {
        position = zox_get_value(e, PixelPosition)
    } else {
        position = get_line_element_mid_point(world, e);
    }
    float2 anchor = float2_zero;    // should i pass this in from parent?
    if (zox_has(e, Anchor)) {
        anchor = zox_get_value(e, Anchor)
    }
    // calculate pixel and real positions
    const int2 position_in_canvas = get_element_pixel_position_global(parent_position, parent_size, position, anchor);
    const float2 position2D = get_element_position(position_in_canvas, canvas_size);
    if (zox_has(e, Position2D)) {
        Position2D *position2D_component = zox_get_mut(e, Position2D)
        position2D_component->value = position2D;
        zox_modified(e, Position2D)
    }
    if (zox_has(e, CanvasPosition)) {
        CanvasPosition *canvasPosition = zox_get_mut(e, CanvasPosition)
        canvasPosition->value = position_in_canvas;
        zox_modified(e, CanvasPosition)
    }
    set_line_element_real_position2D(world, e, position2D, canvas_size, position);
    if (zox_has(e, Children)) {
        int2 size = parent_size;
        if (zox_has(e, PixelSize)) {
            size = zox_get_value(e, PixelSize)
        }
        const Children *children = zox_get(e, Children)
        if (!children->value) return;
        for (int i = 0; i < children->length; i++) {
            const ecs_entity_t child = children->value[i];
            set_element_position(world, child, position_in_canvas, size, canvas_size);
        }
    }
}
