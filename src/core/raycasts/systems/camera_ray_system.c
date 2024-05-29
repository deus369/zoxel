void CameraRaySystem(ecs_iter_t *it) {
    const float2 viewport_position = (float2) { 0.5f, 0.5f };
    zox_field_in(FrustumCorners, frustumCornerss, 1)
    zox_field_out(RaycastOrigin, raycastOrigins, 2)
    zox_field_out(RaycastNormal, raycastNormals, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(FrustumCorners, frustumCornerss, frustumCorners)
        if (!frustumCorners->value) continue;
        zox_field_o(RaycastOrigin, raycastOrigins, origin)
        zox_field_o(RaycastNormal, raycastNormals, normal)
        Ray ray = camera_point_to_ray(frustumCorners->value, viewport_position);
        origin->value = ray.origin;
        normal->value = ray.normal;
        // zox_log(" > ray [%fx%fx%f] - n [%fx%fx%f]\n", ray.origin.x, ray.origin.y, ray.origin.z, ray.normal.x, ray.normal.y, ray.normal.z)
    }
} zox_declare_system(CameraRaySystem)
