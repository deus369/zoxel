void calculate_frustum_corners_d3(const float4x4 view_projection_matrix, double3 *frustum) {
    const float4x4 inverse_view_projection_matrix = float4x4_inverse(view_projection_matrix);
    const float4x4 mat = inverse_view_projection_matrix;
    frustum[0] = (double3) { -1, -1, -1 };
    frustum[1] = (double3) { 1, -1, -1 };
    frustum[2] = (double3) { 1, 1, -1 };
    frustum[3] = (double3) { -1, 1, -1 };
    frustum[4] = (double3) { -1, -1, 1 };
    frustum[5] = (double3) { 1, -1, 1 };
    frustum[6] = (double3) { 1, 1, 1 };
    frustum[7] = (double3) { -1, 1, 1 };
    for (int i = 0; i < 8; i++) {
        const double4 corner = double4_from_double3(frustum[i], 1);
        const double4 world_corner = float4x4_multiply_double4(mat, corner);
        frustum[i] = double3_divide_double((double3) { world_corner.x, world_corner.y, world_corner.z }, world_corner.w);
    }
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


// clockwise or counter clockwise determines normal direction
double3 generate_plane_normal_d3(const double3 point_a, const double3 point_b, const double3 point_c) {
    const double3 vector_ab = double3_sub(point_a, point_b);
    const double3 vector_ac = double3_sub(point_a, point_c);
    return double3_normalize(double3_cross(vector_ab, vector_ac));
}

plane calculate_plane_from_points_d3(const double3 point_a, const double3 point_b, const double3 point_c) {
    plane result_plane;
    result_plane.normal = double3_to_float3(generate_plane_normal_d3(point_a, point_b, point_c));
    result_plane.distance = double3_dot(float3_to_double3(result_plane.normal), point_a);
    return result_plane;
}

void calculate_planes_from_frustum_d3(const double3 *frustum, plane *planes) {
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