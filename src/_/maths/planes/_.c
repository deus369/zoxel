// These scripts are just TOO PLANE hah!

#include "plane.c"
#include "conv.c"
#include "frustum.c"
#include "bounds.c"
#include "frustum_f3.c"
#include "frustum_d3.c" // we need double precision for camera
#include "debug.c"
#include "tests.c"
// #include "fun.c"

// Scraps




/*
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
}*/

// clockwise or counter clockwise determines normal direction
/*float3 generate_plane_normal_f3(const float3 point_a, const float3 point_b, const float3 point_c) {
    const float3 vector_ab = float3_subtract(point_a, point_b);
    const float3 vector_ac = float3_subtract(point_a, point_c);
    return float3_normalize(float3_cross(vector_ab, vector_ac));
}*/

/*plane calculate_plane_from_points_f3(const float3 point_a, const float3 point_b, const float3 point_c) {
    plane result_plane;
    result_plane.normal = generate_plane_normal_f3(point_a, point_b, point_c);
    result_plane.distance = float3_dot(result_plane.normal, point_a);
    return result_plane;
}*/

/*void calculate_planes_from_frustum_f3(const float3 *frustum, plane *planes) {
    // Left is (-1,-1,-1) -> (-1,+1,-1) -> (-1,-1,+1) => counter clockwise
    planes[0] = calculate_plane_from_points_f3(frustum[0], frustum[3], frustum[4]); // 0, 3, 4, 7 L
    // Right is (+1,-1,+1) ->  (+1,+1,-1) -> (+1,-1,-1) => clockwise
    planes[1] = calculate_plane_from_points_f3(frustum[5], frustum[2], frustum[1]); // 1, 2, 5, 6 R
    // Down is (-1,-1,-1) -> (+1,-1,-1) -> (-1,-1,+1) => counter clockwise
    planes[2] = calculate_plane_from_points_f3(frustum[4], frustum[1], frustum[0]); // 0, 1, 4, 5 B
    // Up is (-1,+1,+1) -> (+1,+1,+1) -> (-1,+1,-1) => clockwise
    planes[3] = calculate_plane_from_points_f3(frustum[3], frustum[6], frustum[7]); // 2, 3, 6, 7 T
    // Near is 1 (+1,-1,-1) -> 2 (+1,+1,-1) -> 3 (-1,+1,-1) => clockwise
    planes[4] = calculate_plane_froeeeeeeeeeeeeeeem_points_f3(frustum[1], frustum[2], frustum[3]); // 0, 1, 2, 3 N
    // Far is 1 (+1,-1,+1) -> 2 (+1,+1,+1) -> 3 (-1,+1,+1) => counter clockwise
    planes[5] = calculate_plane_from_points_f3(frustum[7], frustum[6], frustum[5]); // 4, 5, 6, 7 F
}*/
