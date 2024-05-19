void calculate_frustum_bounds(const float3 *corners, float6 *bounds) {
    // Initialize bounds with extreme values
    bounds->x = bounds->z = bounds->u = FLT_MAX;
    bounds->y = bounds->w = bounds->v = -FLT_MAX;
    // Iterate through all the corners to find the min and max for x, y, and z
    for (int i = 0; i < 8; i++) {
        if (corners[i].x < bounds->x) bounds->x = corners[i].x;
        if (corners[i].x > bounds->y) bounds->y = corners[i].x;

        if (corners[i].y < bounds->z) bounds->z = corners[i].y;
        if (corners[i].y > bounds->w) bounds->w = corners[i].y;

        if (corners[i].z < bounds->u) bounds->u = corners[i].z;
        if (corners[i].z > bounds->v) bounds->v = corners[i].z;
    }
    // zox_log(" b x[%.1fx%.1f] y[%.1fx%.1f] z[%.1fx%.1f]\n", bounds->x, bounds->y, bounds->z, bounds->w, bounds->u, bounds->v)
}


unsigned char is_bounds_in_position_bounds(const float6 limits, const bounds b) {
    // Calculate the minimum and maximum coordinates of bounds b
    float3 min_b, max_b;
    min_b.x = b.center.x - b.extents.x;
    min_b.y = b.center.y - b.extents.y;
    min_b.z = b.center.z - b.extents.z;
    max_b.x = b.center.x + b.extents.x;
    max_b.y = b.center.y + b.extents.y;
    max_b.z = b.center.z + b.extents.z;
    // zox_log(" cb x[%.1fx%.1f] y[%.1fx%.1f] z[%.1fx%.1f]\n", min_b.x, max_b.x, min_b.y, max_b.y, min_b.z, max_b.z)
    // printf(" l x[%.1fx%.1f] y[%.1fx%.1f] z[%.1fx%.1f]\n", limits.x, limits.y, limits.z, limits.w, limits.u, limits.v);
    // Check if b is within the limits
    if (max_b.x < limits.x || min_b.x > limits.y || max_b.y < limits.z || min_b.y > limits.w || max_b.z < limits.u || min_b.z > limits.v) return 0;
    else return 1;
}
