unsigned char is_outside_plane(const plane p, const float3 point) {
    return -float3_dot(p.normal, point) + p.distance < 0;
}

// checks if bounds point is outside of plane - test TestPlanesAABB
unsigned char is_in_frustum(const plane *planes, bounds b) {
    // float3_multiply_float_p(&b.center, -1); // whyy i g otta do this??
    for (unsigned char i = 0; i < 6; i++) { // Just Z for now!
        plane check_plane = planes[i];
        float3 normal_sign = float3_sign(check_plane.normal);
        const float3 bounds_point = float3_add(b.center, float3_multiply_float3(b.extents, normal_sign));
        if (is_outside_plane(check_plane, bounds_point)) return 0;
    }
    return 1; // inside all planes
}

float3* calculate_frustum_corners(const float4x4 view_projection_matrix) {
    const  float4x4 inverse_view_projection_matrix = float4x4_inverse(view_projection_matrix);
    float3 *frustum = malloc(sizeof(float3) * 8);
    frustum[0] = (float3) { -1, -1, -1 };
    frustum[1] = (float3) { 1, -1, -1 };
    frustum[2] = (float3) { 1, 1, -1 };
    frustum[3] = (float3) { -1, 1, -1 };
    frustum[4] = (float3) { -1, -1, 1 };
    frustum[5] = (float3) { 1, -1, 1 };
    frustum[6] = (float3) { 1, 1, 1 };
    frustum[7] = (float3) { -1, 1, 1 };
    for (int i = 0; i < 8; i++) {
        const float4 point_homogeneous = float4_from_float3(frustum[i], 1);
        const float4 transformed_point = float4x4_multiply_float4(inverse_view_projection_matrix, point_homogeneous);
        frustum[i] = float3_divide_float((float3) { transformed_point.x, transformed_point.y, transformed_point.z }, transformed_point.w);
    }
    return frustum;
}

// const float4x4 view_matrix, const float4x4 view_projection_matrix,
float3* calculate_frustum_corners_old(const float4x4 projection_matrix, const float4x4 transform_matrix) {
    // const float4x4 inverse_projection_matrix = float4x4_inverse_precise(projection_matrix);
    float3 *frustum = malloc(sizeof(float3) * 8);
    frustum[0] = (float3) { -1, -1, -1 };
    frustum[1] = (float3) { 1, -1, -1 };
    frustum[2] = (float3) { 1, 1, -1};
    frustum[3] = (float3) { -1, 1, -1 };
    frustum[4] = (float3) { -1, -1, 1 };
    frustum[5] = (float3) { 1, -1, 1 };
    frustum[6] = (float3) { 1, 1, 1 };
    frustum[7] = (float3) { -1, 1, 1 };
    // Apply projection matrix to transform from NDC to view space
    const float4x4 inverse_projection_matrix = float4x4_inverse(projection_matrix);
    for (int i = 0; i < 8; i++) {
        float4 point_homogeneous = float4_from_float3(frustum[i], 1.0f);
        float4 transformed_point = float4x4_multiply_float4(inverse_projection_matrix, point_homogeneous);
        frustum[i] = float3_divide_float((float3) { transformed_point.x, transformed_point.y, transformed_point.z }, transformed_point.w);
        frustum[i] = float4x4_multiply_float3(transform_matrix, frustum[i]);
        // zox_log(" %i: %fx%fx%f\n", i, frustum[i].x, frustum[i].y, frustum[i].z)
    }
    return frustum;
}

/*void get_corners(const bounds b, float3 corners[8]) {
    const float3 center = b.center;
    const float3 extents = b.extents;
    // Compute the corners of the bounding box
    corners[0] = float3_add(center, (float3){-extents.x, -extents.y, -extents.z});
    corners[1] = float3_add(center, (float3){-extents.x, -extents.y, extents.z});
    corners[2] = float3_add(center, (float3){-extents.x, extents.y, -extents.z});
    corners[3] = float3_add(center, (float3){-extents.x, extents.y, extents.z});
    corners[4] = float3_add(center, (float3){extents.x, -extents.y, -extents.z});
    corners[5] = float3_add(center, (float3){extents.x, -extents.y, extents.z});
    corners[6] = float3_add(center, (float3){extents.x, extents.y, -extents.z});
    corners[7] = float3_add(center, (float3){extents.x, extents.y, extents.z});
}

unsigned char is_in_frustum(const plane *planes, const bounds b) {
    // Check if all corners are inside planes 4 and 5
    for (unsigned char i = 4; i <= 5; i++) {
        const float3 normal = planes[i].normal;
        // Get the corners of the bounding box
        float3 corners[8];
        get_corners(b, corners);
        // Check each corner against the plane
        unsigned char all_inside = 1;
        for (unsigned char j = 0; j < 8; j++) {
            const float3 bounds_point = corners[j];
            if (!compare_point_on_plane(planes[i], bounds_point)) {
                all_inside = 0;
                break;
            }
        }
        if (!all_inside) return 0; // If any corner is outside, return false
    }
    return 1; // All corners are inside both planes, return true
}*/
// returns 1 or 2 if outside or on plane, 0 if under plane
/*unsigned char compare_point_on_plane(const plane p, const float3 point) {
    const float distance = float3_dot(point, p.normal) + p.distance;
    if (distance < 0) return 0; // point opposite normal
    else if (distance > 0) return 1; // point on normal side of plane
    else return 2; // point on line
}*/

