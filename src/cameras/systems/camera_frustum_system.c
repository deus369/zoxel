extern void draw_frustum(ecs *world, float3 *frustum, const color_rgb debug_color);

void CameraFrustumSystem(iter *it) {
    if (zox_cameras_disable_streaming) {
        return;
    }
    zox_sys_begin()
    zox_sys_in(ViewMatrix)
    zox_sys_out(FrustumCorners)
    zox_sys_out(Position3DBounds)
    zox_sys_out(CameraPlanes)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ViewMatrix, viewMatrix)
        zox_sys_o(CameraPlanes, cameraPlanes)
        zox_sys_o(FrustumCorners, frustumCorners)
        zox_sys_o(Position3DBounds, position3DBounds)
        calculate_frustum_corners_d3(viewMatrix->value, frustumCorners->value);
        calculate_frustum_bounds_d3(frustumCorners->value, &position3DBounds->value);
        calculate_planes_from_frustum_d3(frustumCorners->value, cameraPlanes->value);
    }
} zoxd_system(CameraFrustumSystem)