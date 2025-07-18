// Remember: So i finally gett  it, we have 6 planes, normal + distance are their formula
// A normal is direction plane faces, distance is from origin, you can draw this actually
// we have 6, they overlap, but they should all be forming a shape, facing out? idk
// Our check checks if the bounding box intersects with every plane, well checks the side it's on
// if it's not on every side, it's in middle, i.e. inside the cage / frustum shape
// we need to draw these planes. we can get their overlapping 8 points?
// return float3_dot(p.normal, point) >= p.distance;

byte is_outside_plane(const plane p, const float3 point) {
    return float3_dot(p.normal, point) - p.distance >= 0;
}

// checks if bounds is inside 6 planes
byte is_entire_bounds_in_frustum(const plane *planes, bounds b) {
    for (byte i = 0; i < 6; i++) {
        const plane p = planes[i];
        const float3 normal_sign = float3_sign(p.normal);
        const float3 point = float3_add(b.center, float3_multiply_float3(b.extents, normal_sign));
        if (is_outside_plane(p, point)) return 0;
    }
    return 1;
}

// checks if any part of bounds is inside 6 planes
byte is_in_frustum(const plane *planes, bounds b) {
    float3 point;
    for (byte i = 0; i < 6; i++) {
        const plane p = planes[i];
        byte all_outside_plane = 1;
        point = float3_add(b.center, (float3) { -b.extents.x, -b.extents.y, -b.extents.z });
        if (!is_outside_plane(p, point)) all_outside_plane = 0;
        point = float3_add(b.center, (float3) { -b.extents.x, -b.extents.y, +b.extents.z });
        if (!is_outside_plane(p, point)) all_outside_plane = 0;
        point = float3_add(b.center, (float3) { -b.extents.x, +b.extents.y, -b.extents.z });
        if (!is_outside_plane(p, point)) all_outside_plane = 0;
        point = float3_add(b.center, (float3) { -b.extents.x, +b.extents.y, +b.extents.z });
        if (!is_outside_plane(p, point)) all_outside_plane = 0;
        point = float3_add(b.center, (float3) { +b.extents.x, -b.extents.y, -b.extents.z });
        if (!is_outside_plane(p, point)) all_outside_plane = 0;
        point = float3_add(b.center, (float3) { +b.extents.x, -b.extents.y, +b.extents.z });
        if (!is_outside_plane(p, point)) all_outside_plane = 0;
        point = float3_add(b.center, (float3) { +b.extents.x, +b.extents.y, -b.extents.z });
        if (!is_outside_plane(p, point)) all_outside_plane = 0;
        point = float3_add(b.center, (float3) { +b.extents.x, +b.extents.y, +b.extents.z });
        if (!is_outside_plane(p, point)) all_outside_plane = 0;
        if (all_outside_plane) return 0;
    }
    return 1;
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

// clockwise or counter clockwise determines normal direction
float3 generate_plane_normal_f3(const float3 point_a, const float3 point_b, const float3 point_c) {
    const float3 vector_ab = float3_subtract(point_a, point_b);
    const float3 vector_ac = float3_subtract(point_a, point_c);
    return float3_normalize(float3_cross(vector_ab, vector_ac));
}

plane calculate_plane_from_points_f3(const float3 point_a, const float3 point_b, const float3 point_c) {
    plane result_plane;
    result_plane.normal = generate_plane_normal_f3(point_a, point_b, point_c);
    result_plane.distance = float3_dot(result_plane.normal, point_a);
    return result_plane;
}

void calculate_planes_from_frustum_f3(const float3 *frustum, plane *planes) {
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
