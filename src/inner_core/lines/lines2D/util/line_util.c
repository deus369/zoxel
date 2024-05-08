int4 get_new_line_position(const float2 real_position2D, const float2 canvas_size_f, const float aspect_ratio, const int2 parent_position, const int4 local_position) {
    const int2 new_mid_point = (int2) { ceil((real_position2D.x / aspect_ratio + 0.5f) * canvas_size_f.x), ((real_position2D.y + 0.5f) * canvas_size_f.y) };
    const int2 delta = int2_sub(new_mid_point, parent_position);
    int4 output = local_position;
    int4_add_int2(&output, delta);
    return output;
}


void set_line_element_real_position2D(ecs_world_t *world, const ecs_entity_t e, const float2 real_position2D, const int2 canvas_size, const int2 parent_position) {
    if (zox_has(e, LinePosition2D)) {
        const float2 canvas_size_f = int2_to_float2(canvas_size);
        const float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
        const LineLocalPosition2D *lineLocalPosition2D = zox_get(e, LineLocalPosition2D)
        const int4 new_line_position = get_new_line_position(real_position2D, canvas_size_f, aspect_ratio, parent_position, lineLocalPosition2D->value);
        LinePosition2D *linePosition2D = zox_get_mut(e, LinePosition2D)
        linePosition2D->value = new_line_position;
        zox_modified(e, LinePosition2D);
    }
}

int2 get_line_element_mid_point(ecs_world_t *world, const ecs_entity_t e) {
    if (zox_has(e, LineLocalPosition2D)) {
        const LineLocalPosition2D *lineLocalPosition2D = ecs_get(world, e, LineLocalPosition2D);
        const int2 xy_line = int4_xy(lineLocalPosition2D->value);
        int2 pixel_position = int4_zw(lineLocalPosition2D->value);
        int2_subtract(&pixel_position, xy_line);
        int2_divide_int_p(&pixel_position, 2);
        int2_add_p(&pixel_position, xy_line);
        return pixel_position;
    }
    return int2_zero;
}
