void CameraFrustumSystem(ecs_iter_t *it) {
    if (zox_cameras_disable_streaming) return;
    zox_field_in(ViewMatrix, viewMatrixs, 1)
    zox_field_in(TransformMatrix, transformMatrixs, 2)
    // zox_field_in(ProjectionMatrix, projectionMatrixs, 3)
    zox_field_out(CameraPlanes, cameraPlaness, 4)
    zox_field_out(FrustumCorners, frustumCornerss, 5)
    zox_field_out(Position3DBounds, position3DBoundss, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ViewMatrix, viewMatrixs, viewMatrix)
        zox_field_i_in(TransformMatrix, transformMatrixs, transformMatrix)
        // zox_field_i_in(ProjectionMatrix, projectionMatrixs, projectionMatrix)
        zox_field_o(CameraPlanes, cameraPlaness, cameraPlanes)
        zox_field_o(FrustumCorners, frustumCornerss, frustumCorners)
        zox_field_o(Position3DBounds, position3DBoundss, position3DBounds)
        if (!cameraPlanes->value) {
            cameraPlanes->length = 6;
            cameraPlanes->value = malloc(cameraPlanes->length * sizeof(plane));
        }
        if (!frustumCorners->value) {
            frustumCorners->length = 8;
            frustumCorners->value = malloc(frustumCorners->length * sizeof(float3));
        }
        // calculate_frustum_planes_alternative(viewMatrix->value, cameraPlanes->value);
        frustumCorners->value = calculate_frustum_corners(viewMatrix->value);
        calculate_frustum_planes(viewMatrix->value, cameraPlanes->value, &position3DBounds->value);
        debug_camera_transform = transformMatrix->value;
        // fix_frustum_normals(transformMatrix->value, cameraPlanes->value);
        // calculate_frustum_planes2(transformMatrix->value, projectionMatrix->value, cameraPlanes->value);
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
#endif
    }
} zox_declare_system(CameraFrustumSystem)
