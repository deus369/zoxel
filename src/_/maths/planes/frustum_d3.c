void calculate_frustum_corners_d3(
    const float4x4 view_projection_matrix,
    double3 *frustum
) {
    frustum[0] = (double3) { -1, -1, -1 };
    frustum[1] = (double3) { 1, -1, -1 };
    frustum[2] = (double3) { 1, 1, -1 };
    frustum[3] = (double3) { -1, 1, -1 };
    frustum[4] = (double3) { -1, -1, 1 };
    frustum[5] = (double3) { 1, -1, 1 };
    frustum[6] = (double3) { 1, 1, 1 };
    frustum[7] = (double3) { -1, 1, 1 };
    const float4x4 inv = float4x4_inverse_safe(view_projection_matrix);
    for (int i = 0; i < 8; i++) {
        const double4 corner = double4_from_double3(frustum[i], 1);
        const double4 world_corner = float4x4_multiply_double4(inv, corner);
        frustum[i] = double3_divide_double(
            (double3) { world_corner.x, world_corner.y, world_corner.z },
                                           world_corner.w);
    }
}

// clockwise or counter clockwise determines normal direction
double3 generate_plane_normal_d3(const double3 a, const double3 b, const double3 c) {
    const double3 ab = double3_sub(a, b);
    const double3 ac = double3_sub(a, c);
    return double3_normalize(double3_cross(ab, ac));
}

plane calculate_plane_from_points_d3(const double3 a, const double3 b, const double3 c) {
    plane result_plane;
    result_plane.normal = double3_to_float3(generate_plane_normal_d3(a, b, c));
    result_plane.distance = double3_dot(float3_to_double3(result_plane.normal), a);
    return result_plane;
}

// Original
void calculate_planes_from_frustum_d3_outwards(const double3 *frustum, plane *planes) {
    // Left is (-1,-1,-1) -> (-1,+1,-1) -> (-1,-1,+1) => counter clockwise
    planes[0] = calculate_plane_from_points_d3(frustum[0], frustum[3], frustum[4]); // 0, 3, 4, 7 L
    // Right is (+1,-1,+1) ->  (+1,+1,-1) -> (+1,-1,-1) => clockwise
    planes[1] = calculate_plane_from_points_d3(frustum[5], frustum[2], frustum[1]); // 1, 2, 5, 6 R
    // Down is (-1,-1,-1) -> (+1,-1,-1) -> (-1,-1,+1) => counter clockwise
    planes[2] = calculate_plane_from_points_d3(frustum[4], frustum[1], frustum[0]); // 0, 1, 4, 5 B
    // Up is (-1,+1,+1) -> (+1,+1,+1) -> (-1,+1,-1) => clockwise
    planes[3] = calculate_plane_from_points_d3(frustum[3], frustum[6], frustum[7]); // 2, 3, 6, 7 T
    // Near is 1 (+1,-1,-1) -> 2 (+1,+1,-1) -> 3 (-1,+1,-1) => clockwise
    planes[4] = calculate_plane_from_points_d3(frustum[1], frustum[2], frustum[3]); // 0, 1, 2, 3 N
    // Far is 1 (+1,-1,+1) -> 2 (+1,+1,+1) -> 3 (-1,+1,+1) => counter clockwise
    planes[5] = calculate_plane_from_points_d3(frustum[7], frustum[6], frustum[5]); // 4, 5, 6, 7 F
}

void calculate_planes_from_frustum_d3_inwards(const double3 *frustum, plane *planes) {
    // Flip winding by swapping b and c on each call:

    // Left (swap 3 and 4)
    planes[0] = calculate_plane_from_points_d3(frustum[0], frustum[4], frustum[3]);

    // Right (swap 2 and 1)
    planes[1] = calculate_plane_from_points_d3(frustum[5], frustum[1], frustum[2]);

    // Bottom (swap 1 and 0)
    planes[2] = calculate_plane_from_points_d3(frustum[4], frustum[0], frustum[1]);

    // Top (swap 6 and 7)
    planes[3] = calculate_plane_from_points_d3(frustum[3], frustum[7], frustum[6]);

    // Near (swap 2 and 3)
    planes[4] = calculate_plane_from_points_d3(frustum[1], frustum[3], frustum[2]);

    // Far (swap 6 and 5)
    planes[5] = calculate_plane_from_points_d3(frustum[7], frustum[5], frustum[6]);
}


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
