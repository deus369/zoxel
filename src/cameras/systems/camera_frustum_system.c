void CameraFrustumSystem(ecs_iter_t *it) {
    if (zox_cameras_disable_streaming) return;
    zox_field_in(ViewMatrix, viewMatrixs, 1)
    zox_field_out(FrustumCorners, frustumCornerss, 2)
    zox_field_out(Position3DBounds, position3DBoundss, 3)
    zox_field_out(CameraPlanes, cameraPlaness, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ViewMatrix, viewMatrixs, viewMatrix)
        zox_field_o(CameraPlanes, cameraPlaness, cameraPlanes)
        zox_field_o(FrustumCorners, frustumCornerss, frustumCorners)
        zox_field_o(Position3DBounds, position3DBoundss, position3DBounds)
        if (!cameraPlanes->value) {
            cameraPlanes->length = 6;
            cameraPlanes->value = malloc(cameraPlanes->length * sizeof(plane));
        }
        if (!frustumCorners->value) {
            frustumCorners->length = 8;
            frustumCorners->value = malloc(frustumCorners->length * sizeof(double3));
        }
        calculate_frustum_corners_d3(viewMatrix->value, frustumCorners->value);
        calculate_frustum_bounds_d3(frustumCorners->value, &position3DBounds->value);
        calculate_planes_from_frustum_d3(frustumCorners->value, cameraPlanes->value);
    }
} zox_declare_system(CameraFrustumSystem)

/*        debug_camera_transform = transformMatrix->value;
        // fix_frustum_normals(transformMatrix->value, cameraPlanes->value);
#ifdef zox_test_frustum
        // plane *planes2 = create_test_planes(16);
        plane *planes2 = create_test_planes_position(debug_plane_position, debug_plane_distance);
        for (int i = 0; i < 6; i++) cameraPlanes->value[i] = planes2[i];
        free(planes2);
#endif
#ifdef zox_test_frustum2
        plane *planes2 = create_test_planes_position((float3) { transformMatrix->value.w.x, transformMatrix->value.w.y, transformMatrix->value.w.z }, debug_plane_distance);
        for (int i = 0; i < 6; i++) cameraPlanes->value[i] = planes2[i];
        free(planes2);
        // normalize_planes(cameraPlanes->value);
#endif*/
