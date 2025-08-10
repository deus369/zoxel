
void CameraFrustumSystem(iter *it) {
    if (zox_cameras_disable_streaming) {
        return;
    }
    zox_sys_begin();
    zox_sys_in(ViewMatrix);
    zox_sys_out(FrustumCorners);
    zox_sys_out(Position3DBounds);
    zox_sys_out(CameraPlanes);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ViewMatrix, viewproj);
        zox_sys_o(CameraPlanes, cameraPlanes);
        zox_sys_o(FrustumCorners, corners);
        zox_sys_o(Position3DBounds, bounds);
        calculate_frustum_corners_f3(viewproj->value, corners->value);
        calculate_frustum_bounds_f3(corners->value, &bounds->value);
        calculate_planes_from_frustum_f3(corners->value, cameraPlanes->value);
        // extract_planes_from_viewproj(viewproj->value, cameraPlanes->value);
    }
} zoxd_system(CameraFrustumSystem)