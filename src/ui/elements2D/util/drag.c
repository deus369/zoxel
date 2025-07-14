byte is_log_dragging = 0;

void drag_element(ecs_world_t *world, const ecs_entity_t e, const int2 drag_value) {
    if (!zox_valid(e)) {
        return;
    }
    zox_get_muter(e, PixelPosition, pixel_position)
    pixel_position->value.x += drag_value.x;
    pixel_position->value.y += drag_value.y;
    if (is_log_dragging) {
        zox_log("> dragging [%s] by %ix%i", zox_get_name(e), drag_value.x, drag_value.y)
    }
    if (zox_has(e, DraggableLimits)) {
        zox_geter_value(e, DraggableLimits, int4, drag_bounds)
        limited_element(pixel_position, drag_bounds);
        if (is_log_dragging) {
            zox_log("   - bounded by [%s] by x[%i-%i] y[%i-%i]", zox_get_name(e), drag_bounds.x, drag_value.y, drag_bounds.z, drag_bounds.w)
        }
    }
}
