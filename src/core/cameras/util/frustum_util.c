float3* calculate_frustum_corners(const float4x4 view_projection_matrix) {
    const float4x4 inverse_view_projection_matrix = float4x4_inverse(view_projection_matrix);
    const float4x4 mat = inverse_view_projection_matrix;
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
        const float4 corner = float4_from_float3(frustum[i], 1);
        const float4 world_corner = float4x4_multiply_float4(mat, corner);
        frustum[i] = float3_divide_float((float3) { world_corner.x, world_corner.y, world_corner.z }, world_corner.w);
    }
    return frustum;
}

        /*const float4 world_corner = {
            mat.x.x * corner.x + mat.x.y * corner.y + mat.x.z * corner.z + mat.x.w * corner.w,
            mat.y.x * corner.x + mat.y.y * corner.y + mat.y.z * corner.z + mat.y.w * corner.w,
            mat.z.x * corner.x + mat.z.y * corner.y + mat.z.z * corner.z + mat.z.w * corner.w,
            mat.w.x * corner.x + mat.w.y * corner.y + mat.w.z * corner.z + mat.w.w * corner.w
        };*/


    /*float left = mat.x.w + mat.x.x;
    float right = mat.x.w - mat.x.x;
    float bottom = mat.y.w + mat.y.y;
    float top = mat.y.w - mat.y.y;
    float near = mat.z.w + mat.z.z;
    float far = mat.z.w - mat.z.z;
    frustum[0] = (float3) { left, top, near };
    frustum[1] = (float3) { right, top, near };
    frustum[2] = (float3) { left, bottom, near };
    frustum[3] = (float3) { right, bottom, near };
    frustum[4] = (float3) { left, top, far };
    frustum[5] = (float3) { right, top, far };
    frustum[6] = (float3) { left, bottom, far };
    frustum[7] = (float3) { right, bottom, far };*/


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

