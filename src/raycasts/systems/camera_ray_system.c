#ifdef zox_debug_camera_rays
    extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);
#endif

void calculate_new_frustum(ecs_world_t *world, const ecs_entity_t e, const float camera_far, double3 *corners) {
        const TransformMatrix *transformMatrix = zox_get(e, TransformMatrix)
        const FieldOfView *sysOfView = zox_get(e, FieldOfView)
        const CameraNearDistance *cameraNearDistance = zox_get(e, CameraNearDistance)
        const ScreenDimensions *screenDimensions = zox_get(e, ScreenDimensions)
        float screen_y = (float) screenDimensions->value.y;
        if(screen_y <= 0) screen_y = 1;
        const float aspect_ratio = ((float) screenDimensions->value.x) / ((float) screen_y);
        float4x4 projection_matrix;
        calculate_perspective_projection_matrix(&projection_matrix, aspect_ratio, cameraNearDistance->value, camera_far, sysOfView->value);
        const float4x4 view_matrix = float4x4_inverse(transformMatrix->value);
        const float4x4 view_transform_matrix = float4x4_multiply(view_matrix, projection_matrix);
        calculate_frustum_corners_d3(view_transform_matrix, corners);
}

// remember: frustum is having precision errors for rays
void CameraRaySystem(ecs_iter_t *it) {
    const float max_ray_distance = 1;
    const double2 viewport_position = (double2) { 0.5, 0.5 };
    zox_sys_world()
    zox_sys_begin()
    zox_sys_out(RaycastOrigin)
    zox_sys_out(RaycastNormal)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(RaycastOrigin, origin)
        zox_sys_o(RaycastNormal, normal)
        // Ray ray = camera_point_to_ray_d3(frustumCorners->value, viewport_position);
        // camera far for ray system, must be small due to limitations of ray math
        // todo: either get normal frustum to work perfectly or bake this so we can cast multiple raycasts with tthe same closer frustum!
        zox_sys_e()
        double3 corners[8];
        calculate_new_frustum(world, e, max_ray_distance, corners);
        // this lerps our ray b based on frustum
        Ray ray = camera_point_to_ray_d3(corners, viewport_position);
        origin->value = ray.origin;
        normal->value = ray.normal;
        // zox_log(" > ray [%fx%fx%f] - n [%fx%fx%f]\n", ray.origin.x, ray.origin.y, ray.origin.z, ray.normal.x, ray.normal.y, ray.normal.z)
#ifdef zox_debug_camera_rays
        render_line3D(world, ray.origin, float3_add(ray.origin, float3_scale(ray.normal, 8)), color_rgb_white);
#endif
    }
} zoxd_system(CameraRaySystem)
