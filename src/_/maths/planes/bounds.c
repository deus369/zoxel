// checks if bounds is inside 6 planes
byte is_entire_bounds_in_frustum(const plane *planes, bounds b) {
    for (byte i = 0; i < 6; i++) {
        const plane p = planes[i];
        const float3 normal_sign = float3_sign(p.normal);
        const float3 point = float3_add(b.center, float3_scale3(b.extents, normal_sign));
        if (is_outside_plane(p, point)) return 0;
    }
    return 1;
}