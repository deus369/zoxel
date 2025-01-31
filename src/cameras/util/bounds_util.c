void calculate_frustum_bounds_d3(const double3 *corners, float6 *bounds) {
    bounds->x = bounds->z = bounds->u = FLT_MAX;
    bounds->y = bounds->w = bounds->v = -FLT_MAX;
    for (int i = 0; i < 8; i++) {
        if (corners[i].x < bounds->x) bounds->x = corners[i].x;
        if (corners[i].x > bounds->y) bounds->y = corners[i].x;
        if (corners[i].y < bounds->z) bounds->z = corners[i].y;
        if (corners[i].y > bounds->w) bounds->w = corners[i].y;
        if (corners[i].z < bounds->u) bounds->u = corners[i].z;
        if (corners[i].z > bounds->v) bounds->v = corners[i].z;
    }
}

unsigned char is_bounds_in_position_bounds(const float6 limits, const bounds b) {
    const float3 min_b = float3_sub(b.center, b.extents);
    const float3 max_b = float3_add(b.center, b.extents);
    return (!(max_b.x < limits.x || min_b.x > limits.y || max_b.y < limits.z || min_b.y > limits.w || max_b.z < limits.u || min_b.z > limits.v));
}
