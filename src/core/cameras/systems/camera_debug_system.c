extern ecs_entity_t spawn_cube_lines(ecs_world_t *world, const float3 center, const float3 extents, const float thickness, const double life_time, const color_rgb line_color);
extern ecs_entity_t spawn_line3D_colored(ecs_world_t *world, const float3 pointA, const float3 pointB, const float thickness, const double life_time, const color_rgb line_color);

void debug_transform(ecs_world_t *world, const float4x4 mat) {
    // Draw lines to represent the view matrix
    const float line_length = 12;
    const double spawn_life_time = 0.05;
    const color_rgb camera_color = (color_rgb) { 55, 55, 55 };
    const color_rgb camera_color2 = (color_rgb) { 0, 0, 255 };
    const float3 camera_position = float4x4_get_position(mat);
    float3 forward = { mat.z.x, mat.z.y, mat.z.z };
    float3 right = { mat.x.x, mat.x.y, mat.x.z };
    float3 up = { mat.y.x, mat.y.y, mat.y.z };
    spawn_line3D_colored(world, camera_position, float3_add(camera_position, float3_multiply_float(forward, line_length)), 2, spawn_life_time, camera_color2);
    spawn_line3D_colored(world, camera_position, float3_add(camera_position, float3_multiply_float(right, line_length)), 2, spawn_life_time, camera_color);
    spawn_line3D_colored(world, camera_position, float3_add(camera_position, float3_multiply_float(up, line_length)), 2, spawn_life_time, camera_color);
}

extern void render_line3D(const float3 a, const float3 b, const color_rgb line_color);

void visualize_frustum(const float4x4 mat, const plane *planes) {
    // Iterate over each plane in the frustum
    for (int i = 0; i < 6; ++i) {
        // Calculate two points on the plane
        float3 point_on_plane = calculate_point_on_plane(planes[i].normal, planes[i].distance * 6);
        float3 opposite_point_on_plane = calculate_point_on_plane(planes[i].normal, -planes[i].distance * 6);
        // point_on_plane = float4x4_multiply_float3(mat, point_on_plane);
        // opposite_point_on_plane = float4x4_multiply_float3(mat, opposite_point_on_plane);
        // Draw a line between these two points to visualize the plane
        render_line3D(point_on_plane, opposite_point_on_plane, (color_rgb) { 255, 255, 0 });
    }
}

void CameraDebugSystem(ecs_iter_t *it) {
    const float line_length = 1024;
    double spawn_life_time = 1.05;
    const color_rgb hit_color = { 0, 255, 0 };
    const color_rgb miss_color = { 255, 0, 0 };
    const bounds test_bounds = { .center = (float3) { 0, 24, 0 }, .extents = (float3) { 2, 2, 2 } };
    const bounds test_bounds2 = { .center = (float3) { 0, -24, 0 }, .extents = (float3) { 2, 2, 2 } };
    zox_iter_world()
    zox_field_in(CameraPlanes, cameraPlaness, 1)
    zox_field_in(TransformMatrix, transformMatrixs, 2)
    for (int i = 0; i < it->count; i++) {
        if (it->entities[i] != main_cameras[0]) continue;
        zox_field_i_in(CameraPlanes, cameraPlaness, cameraPlanes)
        zox_field_i_in(TransformMatrix, transformMatrixs, transformMatrix)
        for (int j = 0; j < 6; j++) {
            const plane planer = cameraPlanes->value[j];
            render_line3D(float3_zero, float3_multiply_float(planer.normal, planer.distance), (color_rgb) { 255, 255, j * 32 });
        }
        // when this works, disable renders based on frustum checks
        unsigned char is_seen = is_in_frustum(cameraPlanes->value, test_bounds);
        color_rgb cube_color = miss_color;
        if (is_seen) cube_color = hit_color;
        spawn_cube_lines(world, test_bounds.center, test_bounds.extents, 1, spawn_life_time, cube_color);
        // spawn_line3D_colored(world, float3_add(test_bounds.center, (float3) { 0, -line_length, 0 }), float3_add(test_bounds.center, (float3) { 0, line_length, 0 }), 0.5f, 0.03, cube_color);
        // spawn_line3D_colored(world, float3_add(test_bounds.center, (float3) { -line_length, 0, 0 }), float3_add(test_bounds.center, (float3) { line_length, 0, 0 }), 0.5f, 0.03, cube_color);
        // spawn_line3D_colored(world, float3_add(test_bounds.center, (float3) { 0, 0, -line_length }), float3_add(test_bounds.center, (float3) { 0, 0, line_length }), 0.5f, 0.03, cube_color);
        // debug_transform(world, transformMatrix->value);
        // visualize_frustum(transformMatrix->value, cameraPlanes->value);
        if (is_seen) zox_log(" > looking at bounds\n")
        else zox_log(" - looking away from bounds\n")
    }
} zox_declare_system(CameraDebugSystem)
