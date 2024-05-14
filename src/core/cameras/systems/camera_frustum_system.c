void CameraFrustumSystem(ecs_iter_t *it) {
    zox_field_in(ViewMatrix, viewMatrixs, 1)
    zox_field_out(CameraPlanes, cameraPlaness, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ViewMatrix, viewMatrixs, viewMatrix)
        zox_field_i_out(CameraPlanes, cameraPlaness, cameraPlanes)
        if (!cameraPlanes->value) {
            cameraPlanes->length = 6;
            cameraPlanes->value = malloc(cameraPlanes->length * sizeof(plane));
        }
        calculate_frustum_planes(viewMatrix->value, cameraPlanes->value);
    }
} zox_declare_system(CameraFrustumSystem)
