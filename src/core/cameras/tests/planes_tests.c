void print_planes(plane *planes) {
    for (unsigned char i = 0; i < 6; i++) {
        zox_log("   - [%i] plane normal [%fx%fx%f] dist [%f]\n", i, planes[i].normal.x, planes[i].normal.y, planes[i].normal.z, planes[i].distance)
    }
}

plane* create_test_planes_position(float3 position, float distance) {
    plane* planes = malloc(6 * sizeof(plane));
    planes[0] = (plane) { { 1, 0, 0 }, position.x + distance };
    planes[1] = (plane) { { -1, 0, 0 }, -position.x + distance };
    planes[2] = (plane) { { 0, 1, 0 }, position.y + distance };
    planes[3] = (plane) { { 0, -1, 0 }, -position.y + distance };
    planes[4] = (plane) { { 0, 0, 1 }, position.z + distance }; // near
    planes[5] = (plane) { { 0, 0, -1 }, -position.z + distance }; // far
    return planes;
}

plane* create_test_planes(float distance) {
    plane* planes = malloc(6 * sizeof(plane));
    planes[0] = (plane) {{ 1.0f, 0.0f, 0.0f }, distance};  // Right plane: x = 1
    planes[1] = (plane) {{-1.0f, 0.0f, 0.0f }, distance};  // Left plane: x = -1
    planes[2] = (plane) {{ 0.0f, 1.0f, 0.0f }, distance};  // Top plane: y = 1
    planes[3] = (plane) {{ 0.0f, -1.0f, 0.0f }, distance}; // Bottom plane: y = -1
    planes[4] = (plane) {{ 0.0f, 0.0f, 1.0f }, distance};  // Far plane: z = 1
    planes[5] = (plane) {{ 0.0f, 0.0f, -1.0f }, distance}; // Near plane: z = -1
    return planes;
}

/*void fill_fake_view_matrix(float4x4 *matrix, const float3 position, const float4 rotation) {
    const float4x4 transform_matrix = float4x4_inverse_precise(float4x4_transform(position, rotation));
   // float4x4 projection_matrix;
    //calculate_perspective_projection_matrix(&projection_matrix, 16 / 9.0f, 0.3f, 60, 1000);
    const float4x4 position_matrix = float4x4_position(float3_reverse(position));
    const float4x4 rotation_matrix = float4x4_rotation(float4_reverse(rotation));
    const float4x4 transform_matrix = float4x4_multiply(position_matrix, rotation_matrix);
    matrix = float4x4_multiply(transform_matrix, projection_matrix);
    *matrix = transform_matrix;
}*/

void fake_plane_data_old(plane *planes) {
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

// data t taken from unity, planes function
void fake_plane_data(plane *planes) {
    // Left Plane
    planes[0].normal.x = 0.53f;
    planes[0].normal.y = 0.0f;
    planes[0].normal.z = 0.85f;
    planes[0].distance = 0.0f;

    // Right Plane
    planes[1].normal.x = -0.53f;
    planes[1].normal.y = 0.0f;
    planes[1].normal.z = 0.85f;
    planes[1].distance = 0.0f;

    // Bottom Plane
    planes[2].normal.x = 0.0f;
    planes[2].normal.y = 0.87f;
    planes[2].normal.z = 0.5f;
    planes[2].distance = 0.0f;

    // Top Plane
    planes[3].normal.x = 0.0f;
    planes[2].normal.y = -0.87f;
    planes[3].normal.z = 0.5f;
    planes[3].distance = 0.0f;

    // Near Plane
    planes[4].normal.x = 0.0f;
    planes[4].normal.y = 0.0f;
    planes[4].normal.z = 1.0f;
    planes[4].distance = -0.3f;

    // Far Plane
    planes[5].normal.x = 0.0f;
    planes[5].normal.y = 0.0f;
    planes[5].normal.z = -1.0f;
    planes[5].distance = 1000;
}

void run_test_frustum(char *label, const float3 camera_position, const float3 camera_euler) {
    /*zox_log(" > test [%s]\n", label)
    // camera
    float4 camera_rotation = quaternion_from_euler(float3_multiply_float(camera_euler, degreesToRadians));

    plane planes[6];
    float4x4 transform_matrix;
    fill_fake_view_matrix(&transform_matrix, camera_position, camera_rotation);
    float4x4 projection_matrix;
    calculate_perspective_projection_matrix(&projection_matrix, 16 / 9.0f, 0.3f, 60, 1000);
    float4x4 vp_matrix = float4x4_multiply(transform_matrix, projection_matrix);
    calculate_frustum_planes(vp_matrix, planes);
    zox_log("   - camera_position [%f %f %f]\n", camera_position.x, camera_position.y, camera_position.z)
    zox_log("   - camera_euler [%f %f %f]\n", camera_euler.x, camera_euler.y, camera_euler.z)
    log_float4x4("vp_matrix", vp_matrix);
    print_planes(planes);

    // bounds
    const float distance_from = 8;
    const float3 extents = { 1, 1, 1 };

    // Define bounding boxes
    bounds bounds_b = { { 0, 0, -distance_from }, extents };
    bounds bounds_c = { { 0, 0, distance_from }, extents };
    bounds bounds_d = { { -distance_from, 0, 0 }, extents };
    bounds bounds_e = { { distance_from, 0, 0 }, extents };
    bounds bounds_f = { { distance_from / 2, 0, distance_from / 2 }, extents };

    // calculate results
    unsigned char result_b = is_in_frustum(planes, bounds_b);
    unsigned char result_c = is_in_frustum(planes, bounds_c);
    unsigned char result_d = is_in_frustum(planes, bounds_d);
    unsigned char result_e = is_in_frustum(planes, bounds_e);
    unsigned char result_f = is_in_frustum(planes, bounds_f);

    // print results
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_b ? "Inside Frustum" : "Outside Frustum", bounds_b.center.x, bounds_b.center.y, bounds_b.center.z)
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_c ? "Inside Frustum" : "Outside Frustum", bounds_c.center.x, bounds_c.center.y, bounds_c.center.z)
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_d ? "Inside Frustum" : "Outside Frustum", bounds_d.center.x, bounds_d.center.y, bounds_d.center.z)
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_e ? "Inside Frustum" : "Outside Frustum", bounds_e.center.x, bounds_e.center.y, bounds_e.center.z)
    zox_log("   - result: %s - bounds [%f %f %f]\n", result_f ? "Inside Frustum" : "Outside Frustum", bounds_f.center.x, bounds_f.center.y, bounds_f.center.z)*/
}

// test function for is_in_frustum
void test_is_in_frustum(char *label) {
    zox_log(" > test fake_planes [%s]\n", label)
    plane planes[6];
    fake_plane_data(planes);
    print_planes(planes);


    const float distance_from = 8;
    const float3 extents = { 1, 1, 1 };

    // Define bounding boxes
    bounds bounds_b = { { 0, 0, -distance_from }, extents };
    bounds bounds_c = { { 0, 0, distance_from }, extents };
    bounds bounds_d = { { -distance_from, 0, 0 }, extents };
    bounds bounds_e = { { distance_from, 0, 0 }, extents };
    bounds bounds_f = { { distance_from / 2, 0, distance_from / 2 }, extents };

    // Print bounding box information
    zox_log("   - bounds_b center: [%f %f %f]\n", bounds_b.center.x, bounds_b.center.y, bounds_b.center.z)
    zox_log("   - bounds_c center: [%f %f %f]\n", bounds_c.center.x, bounds_c.center.y, bounds_c.center.z)
    zox_log("   - bounds_d center: [%f %f %f]\n", bounds_d.center.x, bounds_d.center.y, bounds_d.center.z)
    zox_log("   - bounds_e center: [%f %f %f]\n", bounds_e.center.x, bounds_e.center.y, bounds_e.center.z)
    zox_log("   - bounds_f center: [%f %f %f]\n", bounds_f.center.x, bounds_f.center.y, bounds_f.center.z)

    // calculate results
    unsigned char result_b = is_in_frustum(planes, bounds_b);
    unsigned char result_c = is_in_frustum(planes, bounds_c);
    unsigned char result_d = is_in_frustum(planes, bounds_d);
    unsigned char result_e = is_in_frustum(planes, bounds_e);
    unsigned char result_f = is_in_frustum(planes, bounds_f);

    // Print results
    zox_log("   - result bounds_b: %s\n", result_b ? "Inside Frustum" : "Outside Frustum");
    zox_log("   - result bounds_c: %s\n", result_c ? "Inside Frustum" : "Outside Frustum");
    zox_log("   - result bounds_d: %s\n", result_d ? "Inside Frustum" : "Outside Frustum");
    zox_log("   - result bounds_e: %s\n", result_e ? "Inside Frustum" : "Outside Frustum");
    zox_log("   - result bounds_f: %s\n", result_f ? "Inside Frustum" : "Outside Frustum");
}

// Testing float4x4_inverse function
void test_float4x4_inverse() {
    float4x4 matrix = {
        .x = {1, 2, 3, 4},
        .y = {0, 1, 2, 3},
        .z = {0, 0, 1, 2},
        .w = {0, 0, 0, 1}
    };
    float4x4 invMatrix = float4x4_inverse(matrix);
    zox_log("Inverse Matrix:\n");
    zox_log("[%.2f %.2f %.2f %.2f]\n", invMatrix.x.x, invMatrix.x.y, invMatrix.x.z, invMatrix.x.w)
    zox_log("[%.2f %.2f %.2f %.2f]\n", invMatrix.y.x, invMatrix.y.y, invMatrix.y.z, invMatrix.y.w)
    zox_log("[%.2f %.2f %.2f %.2f]\n", invMatrix.z.x, invMatrix.z.y, invMatrix.z.z, invMatrix.z.w)
    zox_log("[%.2f %.2f %.2f %.2f]\n", invMatrix.w.x, invMatrix.w.y, invMatrix.w.z, invMatrix.w.w)
    /*
            Inverse Matrix:
        [1.00 -2.00 1.00 0.00]
        [0.00 1.00 -2.00 1.00]
        [0.00 0.00 1.00 -2.00]
        [0.00 0.00 0.00 1.00]
    */
}

void test_corners() {
    /*plane planes[6];
    fake_plane_data(planes);
    float3 *corners = find_plane_corners(planes);
    printf("Plane corners:\n");
    for (int i = 0; i < 8; ++i) {
        printf("(%f, %f, %f)\n", corners[i].x, corners[i].y, corners[i].z);
    }
    free(corners);*/
}

// assume initially facing negative direction
void test_frustum_check() {
    test_is_in_frustum("Aa");
    run_test_frustum("A", float3_zero, (float3) { 0, 180, 0 });
    run_test_frustum("B", float3_zero, float3_zero);
    // test_float4x4_inverse();
    run_test_frustum("C", (float3) { 0, 0, -32 }, float3_zero);
    run_test_frustum("D", (float3) { 0, 0, 32 }, float3_zero);

    /*run_test_frustum("c", (float3) { 0, 0, -32 }, float3_zero);
    run_test_frustum("d", (float3) { 0, 0, -6666 }, float3_zero);*/
}


/*
at 0,0,16 planes:
    Plane 1: Normal = (0.70, 0.00, 0.72), Distance = -11.45841;:
    Plane 2: Normal = (-0.70, 0.00, 0.72), Distance = -11.45841;:
    Plane 3: Normal = (0.00, 0.87, 0.50), Distance = -8;:
    Plane 4: Normal = (0.00, -0.87, 0.50), Distance = -8;:
    Plane 5: Normal = (0.00, 0.00, 1.00), Distance = -16.3;:
    Plane 6: Normal = (0.00, 0.00, -1.00), Distance = 1016.133;:
*/
void test_calculate_plane_from_points() {
    // Define test points
    float3 point_a = (float3) { -1, -1, 0 };
    float3 point_b = (float3) { 1, -1, 0 };
    float3 point_c = (float3) { 1, 1, 0 };
    // float3 point_d = (float3) { -1, 1, 0 };

    // Expected normal and distance for a plane in the xy-plane
    float3 expected_normal = (float3) { 0, 0, 1 };
    float expected_distance = 0;

    // Calculate the plane from the test points
    plane result_plane = calculate_plane_from_points(point_a, point_b, point_c); // , point_d);

    // Check if the calculated normal matches the expected normal
    if (!float3_equals(result_plane.normal, expected_normal)) {
        printf("Error: Calculated normal (%f, %f, %f) does not match expected normal (%f, %f, %f)\n",
               result_plane.normal.x, result_plane.normal.y, result_plane.normal.z,
               expected_normal.x, expected_normal.y, expected_normal.z);
    }

    // Check if the calculated distance matches the expected distance
    if (result_plane.distance != expected_distance) {
        printf("Error: Calculated distance %f does not match expected distance %f\n",
               result_plane.distance, expected_distance);
    }
}

void test_calculate_planes_from_frustum() {
    // Define test frustum points
    float3 frustum_points[8] = {
        (float3) { -1, -1, 0 },
        (float3) { 1, -1, 0 },
        (float3) { 1, 1, 0 },
        (float3) { -1, 1, 0 },
        (float3) { -1, -1, 1 },
        (float3) { 1, -1, 1 },
        (float3) { 1, 1, 1 },
        (float3) { -1, 1, 1 }
    };

    // Expected normals and distances for each plane
    float3 expected_normals[6] = {
        (float3) { -1, 0, 0 },   // Left
        (float3) { 1, 0, 0 },   // Right
        (float3) { 0, -1, 0 },   // Down
        (float3) { 0, 1, 0 },  // Up
        (float3) { 0, 0, 1 },  // Near
        (float3) { 0, 0, 1 }    // Far
    };
    float expected_distances[6] = { 1, 1, 1, 1, 0, 1 };  // Distances are all 0 except for the far plane

    // Calculate planes from the test frustum points
    plane planes[6];
    calculate_planes_from_frustum(frustum_points, planes);

    // Check if the calculated normals and distances match the expected values
    for (int i = 0; i < 6; ++i) {
        // printf("Plane %d: Normal: (%f, %f, %f), Distance: %f\n", i, planes[i].normal.x, planes[i].normal.y, planes[i].normal.z, planes[i].distance);
        if (!float3_equals(planes[i].normal, expected_normals[i])) {
            printf("Error: Calculated normal for plane %d [%fx%fx%f] does not match the expected normal [%fx%fx%f].\n", i, planes[i].normal.x, planes[i].normal.y, planes[i].normal.z, expected_normals[i].x, expected_normals[i].y, expected_normals[i].z);
        }
        if (planes[i].distance != expected_distances[i]) {
            printf("Error: Calculated distance for plane %d [%f] does not match the expected distance %f.\n", i, planes[i].distance, expected_distances[i]);
        }
    }
}


void test_planes_again() {
    // Example usage
    /*float4x4 view_projection_matrix = {
        .x = {1, 0, 0, 0},
        .y = {0, 1, 0, 0},
        .z = {0, 0, 1, 0},
        .w = {0, 0, 0, 1}
    };
    plane planes[6];
    calculate_frustum_planes(view_projection_matrix, planes);
    for (int i = 0; i < 6; i++) {
        printf("Plane %d: normal = (%f, %f, %f), distance = %f\n",
               i, planes[i].normal.x, planes[i].normal.y, planes[i].normal.z, planes[i].distance);
    }*/
}
