void print_planes(plane *planes) {
    for (unsigned char i = 0; i < 6; i++) {
        zox_log("   - [%i] plane normal [%fx%fx%f] dist [%f]\n", i, planes[i].normal.x, planes[i].normal.y, planes[i].normal.z, planes[i].distance)
    }
}

void fill_fake_view_matrix(float4x4 *matrix, const float3 position, const float4 rotation) {
    const float4x4 position_matrix = float4x4_position(position);
    const float4x4 rotation_matrix = float4x4_rotation(rotation);
    const float4x4 transform_matrix = float4x4_inverse_position(float4x4_multiply(position_matrix, rotation_matrix));
    float4x4 projection_matrix;
    // aspect, near, far, fov
    calculate_perspective_projection_matrix(&projection_matrix, 1, 1, 100, 60);
    *matrix = float4x4_multiply(transform_matrix, projection_matrix);
}

void fake_plane_data(plane *planes) {
    // Assuming near plane distance
    float near_distance = 0.1f;
    // Assuming far plane distance
    float far_distance = 100.0f;

    // Left Plane
    planes[0].normal.x = -1.0f;
    planes[0].normal.y = 0.0f;
    planes[0].normal.z = 0.0f;
    planes[0].distance = 0.0f;

    // Right Plane
    planes[1].normal.x = 1.0f;
    planes[1].normal.y = 0.0f;
    planes[1].normal.z = 0.0f;
    planes[1].distance = 0.0f;

    // Bottom Plane
    planes[2].normal.x = 0.0f;
    planes[2].normal.y = -1.0f;
    planes[2].normal.z = 0.0f;
    planes[2].distance = 0.0f;

    // Top Plane
    planes[3].normal.x = 0.0f;
    planes[3].normal.y = 1.0f;
    planes[3].normal.z = 0.0f;
    planes[3].distance = 0.0f;

    // Near Plane
    planes[4].normal.x = 0.0f;
    planes[4].normal.y = 0.0f;
    planes[4].normal.z = -1.0f;
    planes[4].distance = near_distance;

    // Far Plane
    planes[5].normal.x = 0.0f;
    planes[5].normal.y = 0.0f;
    planes[5].normal.z = 1.0f;
    planes[5].distance = far_distance;
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
    const float distance_from = 0.99f;
    const float3 extents = { 1, 1, 1 };

    // Define bounding boxes
    bounds bounds_b = { { 0, 0, -distance_from }, extents };
    bounds bounds_c = { { 0, 0, distance_from }, extents };
    bounds bounds_d = { { -distance_from, 0, 0 }, extents };
    bounds bounds_e = { { distance_from, 0, 0 }, extents };

    // calculate results
    unsigned char result_b = is_in_frustum(planes, bounds_b);
    unsigned char result_c = is_in_frustum(planes, bounds_c);
    unsigned char result_d = is_in_frustum(planes, bounds_d);
    unsigned char result_e = is_in_frustum(planes, bounds_e);

    // print results
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_b ? "Inside Frustum" : "Outside Frustum", bounds_b.center.x, bounds_b.center.y, bounds_b.center.z)
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_c ? "Inside Frustum" : "Outside Frustum", bounds_c.center.x, bounds_c.center.y, bounds_c.center.z)
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_d ? "Inside Frustum" : "Outside Frustum", bounds_d.center.x, bounds_d.center.y, bounds_d.center.z)
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_e ? "Inside Frustum" : "Outside Frustum", bounds_e.center.x, bounds_e.center.y, bounds_e.center.z)
}

// test function for is_in_frustum
void test_is_in_frustum(char *label) {
    zox_log(" > test fake_planes [%s]\n", label)
    plane planes[6];
    fake_plane_data(planes);
    print_planes(planes);


    const float distance_from = 1.99f;
    const float3 extents = { 1, 1, 1 };

    // Define bounding boxes
    bounds bounds_b = { { 0, 0, -distance_from }, extents };
    bounds bounds_c = { { 0, 0, distance_from }, extents };
    bounds bounds_d = { { -distance_from, 0, 0 }, extents };
    bounds bounds_e = { { distance_from, 0, 0 }, extents };

    // Print bounding box information
    zox_log("   - bounds_b center: [%f %f %f]\n", bounds_b.center.x, bounds_b.center.y, bounds_b.center.z)
    zox_log("   - bounds_c center: [%f %f %f]\n", bounds_c.center.x, bounds_c.center.y, bounds_c.center.z)
    zox_log("   - bounds_d center: [%f %f %f]\n", bounds_d.center.x, bounds_d.center.y, bounds_d.center.z)
    zox_log("   - bounds_e center: [%f %f %f]\n", bounds_e.center.x, bounds_e.center.y, bounds_e.center.z)

    // calculate results
    unsigned char result_b = is_in_frustum(planes, bounds_b);
    unsigned char result_c = is_in_frustum(planes, bounds_c);
    unsigned char result_d = is_in_frustum(planes, bounds_d);
    unsigned char result_e = is_in_frustum(planes, bounds_e);

    // Print results
    zox_log("   - result bounds_b: %s\n", result_b ? "Inside Frustum" : "Outside Frustum");
    zox_log("   - result bounds_c: %s\n", result_c ? "Inside Frustum" : "Outside Frustum");
    zox_log("   - result bounds_d: %s\n", result_d ? "Inside Frustum" : "Outside Frustum");
    zox_log("   - result bounds_e: %s\n", result_e ? "Inside Frustum" : "Outside Frustum");
}

// assume initially facing negative direction
void test_frustum_check() {
    test_is_in_frustum("z");
    run_test_frustum("a", float3_zero, float3_zero);
    run_test_frustum("b", float3_zero, (float3) { 0, 180, 0 });
    /*run_test_frustum("b", (float3) { 0, 0, 32 }, float3_zero);
    run_test_frustum("c", (float3) { 0, 0, -32 }, float3_zero);
    run_test_frustum("d", (float3) { 0, 0, -6666 }, float3_zero);*/
}
