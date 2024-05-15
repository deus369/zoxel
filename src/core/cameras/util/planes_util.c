void normalize_planes(plane *planes) {
    for (unsigned char i = 0; i < 6; i++) {
        float length = float3_magnitude(planes[i].normal);
        if (length == 0) continue;
        float3_divide_float_p(&planes[i].normal, length);
        planes[i].distance /= length;
    }
}

void calculate_frustum_planes(const float4x4 mat, plane *planes) {
    // left plane > w + x
    planes[0].normal.x = mat.w.x + mat.x.x;
    planes[0].normal.y = mat.w.y + mat.x.y;
    planes[0].normal.z = mat.w.z + mat.x.z;
    planes[0].distance = mat.w.w + mat.x.w;
    // right plane > w - x
    planes[1].normal.x = mat.w.x - mat.x.x;
    planes[1].normal.y = mat.w.y - mat.x.y;
    planes[1].normal.z = mat.w.z - mat.x.z;
    planes[1].distance = mat.w.w - mat.x.w;
    // bottom plane > w + y
    planes[2].normal.x = mat.w.x + mat.y.x;
    planes[2].normal.y = mat.w.y + mat.y.y;
    planes[2].normal.z = mat.w.z + mat.y.z;
    planes[2].distance = mat.w.w + mat.y.w;
    // top plane > w - y
    planes[3].normal.x = mat.w.x - mat.y.x;
    planes[3].normal.y = mat.w.y - mat.y.y;
    planes[3].normal.z = mat.w.z - mat.y.z;
    planes[3].distance = mat.w.w - mat.y.w;
    // near plane > w + z
    planes[4].normal.x = mat.w.x + mat.z.x;
    planes[4].normal.y = mat.w.y + mat.z.y;
    planes[4].normal.z = mat.w.z + mat.z.z;
    planes[4].distance = mat.w.w + mat.z.w;
    // far plane > w - z
    planes[5].normal.x = mat.w.x - mat.z.x;
    planes[5].normal.y = mat.w.y - mat.z.y;
    planes[5].normal.z = mat.w.z - mat.z.z;
    planes[5].distance = mat.w.w - mat.z.w;
    // normalize_planes(planes);
}

// checks if bounds point is outside of plane
unsigned char is_in_frustum(const plane *planes, const bounds target_bounds) {
    for (unsigned char i = 0; i < 6; i++) {
        const plane camera_plane = planes[i];
        const float3 normal_sign = float3_sign(camera_plane.normal);
        const float3 target_point = float3_add(target_bounds.center, float3_multiply_float3(target_bounds.extents, normal_sign));
        const float dot = float3_dot(target_point, camera_plane.normal);
        if (dot + camera_plane.distance < 0) return 0;
    }
    return 1;
}

void fill_fake_view_matrix(float4x4 *matrix, const float3 position, const float4 rotation) {
    const float4x4 position_matrix = float4x4_position(position);
    const float4x4 rotation_matrix = float4x4_rotation(rotation);
    const float4x4 transform_matrix = float4x4_multiply(position_matrix, rotation_matrix);
    float4x4 projection_matrix;
    // aspect, near, far, fov
    calculate_perspective_projection_matrix(&projection_matrix, 1, 1, 100, 60);
    *matrix = float4x4_multiply(float4x4_inverse_position(transform_matrix), projection_matrix);
}

void print_planes(plane *planes) {
    for (unsigned char i = 0; i < 6; i++) {
        zox_log("   - [%i] plane normal [%fx%fx%f] dist [%f]\n", i, planes[i].normal.x, planes[i].normal.y, planes[i].normal.z, planes[i].distance)
    }
}

void run_test_frustum(char *label, const float3 camera_position, const float3 camera_euler) {
    zox_log(" > test [%s]\n", label)
    // camera
    float4 camera_rotation = quaternion_from_euler(float3_multiply_float(camera_euler, degreesToRadians));
    float4x4 camera_matrix;
    plane planes[6];
    fill_fake_view_matrix(&camera_matrix, camera_position, camera_rotation);
    calculate_frustum_planes(camera_matrix, planes);
    zox_log("   - camera_position [%f %f %f]\n", camera_position.x, camera_position.y, camera_position.z)
    zox_log("   - camera_euler [%f %f %f]\n", camera_euler.x, camera_euler.y, camera_euler.z)
    print_planes(planes);
    // bounds
    const float distance_from = 16;
    const float3 extents = { 1, 1, 1 };

    bounds bounds_b = { { 0, 0, -distance_from }, extents };
    unsigned char result_b = is_in_frustum(planes, bounds_b);
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_b ? "Inside Frustum" : "Outside Frustum", bounds_b.center.x, bounds_b.center.y, bounds_b.center.z)

    bounds bounds_c = { { 0, 0, distance_from }, extents };
    unsigned char result_c = is_in_frustum(planes, bounds_c);
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_c ? "Inside Frustum" : "Outside Frustum", bounds_c.center.x, bounds_c.center.y, bounds_c.center.z)

    bounds bounds_d = { { -distance_from, 0, 0 }, extents };
    unsigned char result_d = is_in_frustum(planes, bounds_d);
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_d ? "Inside Frustum" : "Outside Frustum", bounds_d.center.x, bounds_d.center.y, bounds_d.center.z)

    bounds bounds_e = { { distance_from, 0, 0 }, extents };
    unsigned char result_e = is_in_frustum(planes, bounds_e);
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_e ? "Inside Frustum" : "Outside Frustum", bounds_e.center.x, bounds_e.center.y, bounds_e.center.z)
}

// assume initially facing negative direction
void test_frustum_check() {
    run_test_frustum("a", float3_zero, float3_zero);
    // run_test_frustum("b", float3_zero, (float3) { 0, 180, 0 });
    run_test_frustum("b", (float3) { 0, 0, 32 }, float3_zero);
    run_test_frustum("c", (float3) { 0, 0, -32 }, float3_zero);
    run_test_frustum("d", (float3) { 0, 0, -6666 }, float3_zero);
}
