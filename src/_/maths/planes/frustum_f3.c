void calculate_frustum_corners_f3(
    const float4x4 viewproj,
    float3 *frustum
) {
    frustum[0] = (float3) { -1, -1, -1 };
    frustum[1] = (float3) { 1, -1, -1 };
    frustum[2] = (float3) { 1, 1, -1 };
    frustum[3] = (float3) { -1, 1, -1 };
    frustum[4] = (float3) { -1, -1, 1 };
    frustum[5] = (float3) { 1, -1, 1 };
    frustum[6] = (float3) { 1, 1, 1 };
    frustum[7] = (float3) { -1, 1, 1 };
    const float4x4 inv = float4x4_inverse_safe(viewproj);
    for (int i = 0; i < 8; i++) {
        const float4 corner = float4_from_float3(frustum[i], 1);
        const float4 world_corner = float4x4_multiply_float4(inv, corner);
        frustum[i] = float3_divide_float(
            (float3) { world_corner.x, world_corner.y, world_corner.z },
            world_corner.w
        );
    }
}

float3 generate_plane_normal_f3(const float3 a, const float3 b, const float3 c) {
    const float3 vab = float3_sub(a, b);
    const float3 vac = float3_sub(a, c);
    return float3_normalize(float3_cross(vab, vac));
}

plane calculate_plane_from_points_f3(const float3 a, const float3 b, const float3 c) {
    plane p;
    p.normal = generate_plane_normal_f3(a, b, c);
    p.distance = float3_dot(p.normal, a);
    return p;
}

// clockwise or counter clockwise determines normal direction
void calculate_planes_from_frustum_f3(const float3* frustum, plane* planes) {
    // Left is (-1,-1,-1) -> (-1,+1,-1) -> (-1,-1,+1) => counter clockwise
    planes[0] = calculate_plane_from_points_f3(frustum[0], frustum[3], frustum[4]); // 0, 3, 4, 7 L
    // Right is (+1,-1,+1) ->  (+1,+1,-1) -> (+1,-1,-1) => clockwise
    planes[1] = calculate_plane_from_points_f3(frustum[5], frustum[2], frustum[1]); // 1, 2, 5, 6 R
    // Down is (-1,-1,-1) -> (+1,-1,-1) -> (-1,-1,+1) => counter clockwise
    planes[2] = calculate_plane_from_points_f3(frustum[4], frustum[1], frustum[0]); // 0, 1, 4, 5 B
    // Up is (-1,+1,+1) -> (+1,+1,+1) -> (-1,+1,-1) => clockwise
    planes[3] = calculate_plane_from_points_f3(frustum[3], frustum[6], frustum[7]); // 2, 3, 6, 7 T
    // Near is 1 (+1,-1,-1) -> 2 (+1,+1,-1) -> 3 (-1,+1,-1) => clockwise
    planes[4] = calculate_plane_from_points_f3(frustum[1], frustum[2], frustum[3]); // 0, 1, 2, 3 N
    // Far is 1 (+1,-1,+1) -> 2 (+1,+1,+1) -> 3 (-1,+1,+1) => counter clockwise
    planes[5] = calculate_plane_from_points_f3(frustum[7], frustum[6], frustum[5]); // 4, 5, 6, 7 F
}

void calculate_frustum_bounds_f3(const float3 *corners, float6 *bounds) {
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