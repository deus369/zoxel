/*void set_element_position_for_mouse(ecs_world_t *world, const ecs_entity_t e, const int2 position) {
    if (!zox_valid(e)) return;
    PixelPosition *pixel_position = zox_get_mut(e, PixelPosition)
    pixel_position->value += position;
    if (zox_has(e, DraggableLimits)) {
        const int4 drag_bounds = zox_get_value(e, DraggableLimits)
        limited_element(pixel_position, drag_bounds);
    }
    zox_modified(e, PixelPosition)
}*/

void drag_element(ecs_world_t *world, const ecs_entity_t e, const int2 drag_value) {
    if (!zox_valid(e)) return;
    PixelPosition *pixel_position = zox_get_mut(e, PixelPosition)
    pixel_position->value.x += drag_value.x;
    pixel_position->value.y += drag_value.y;
    if (zox_has(e, DraggableLimits)) {
        const int4 drag_bounds = zox_get_value(e, DraggableLimits)
        limited_element(pixel_position, drag_bounds);
    }
    zox_modified(e, PixelPosition)
#ifdef zox_log_ui_dragging
    zox_log(" > dragging window [%lu] by %ix%i\n", e, drag_value.x, drag_value.y)
#endif
}
