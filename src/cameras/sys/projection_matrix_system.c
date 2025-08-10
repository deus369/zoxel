// This should only update when either ScreenDimensions or FieldOfView changes
void ProjectionMatrixSystem(iter *it) {
#ifdef main_thread_projection_matrix_system
    // zox_skip_if_unchanged(1)
#endif
/*
    if (!ecs_query_changed(NULL, it)) return;
*/
#ifdef zox_use_orthographic_projection
    zox_sys_world()
#endif
    zox_sys_begin()
    zox_sys_in(ScreenDimensions)
    zox_sys_in(FieldOfView)
    zox_sys_in(CameraNearDistance)
    zox_sys_out(ProjectionMatrix)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ScreenDimensions, screenDimensions)
        zox_sys_i(FieldOfView, fieldOfView)
        zox_sys_i(CameraNearDistance, cameraNearDistance)
        zox_sys_o(ProjectionMatrix, projectionMatrix)
        if(screenDimensions->value.y <= 0) {
            continue;
        }
        const float aspect_ratio = ((float) screenDimensions->value.x) / ((float) screenDimensions->value.y);
#ifndef zox_use_orthographic_projection
        calculate_perspective_projection_matrix(
            &projectionMatrix->value,
            aspect_ratio,
            cameraNearDistance->value,
            camera_far_distance,
            fieldOfView->value);
#else
        zox_sys_e()
        if (zox_has(e, Camera2D)) {
            calculate_perspective_projection_matrix(
                &projectionMatrix->value,
                aspect_ratio,
                cameraNearDistance->value,
                camera_far_distance,
                fieldOfView->value);
        } else {
            /*znear = 6;
            const float zfar = camera_far_distance;
            const float znear = cameraNearDistance->value;
            const float ymax = znear * tanf(fieldOfView->value * M_PI / 360.0);
            const float xmax = ymax * aspect_ratio;
            ymax = znear * tanf(fieldOfView->value * M_PI / 360.0);
            xmax = ymax * aspect_ratio;
            calculate_orthographic_projection_matrix(&projectionMatrix->value, -xmax, xmax, -ymax, ymax, znear, zfar);*/
        }
#endif
    }
} zoxd_system(ProjectionMatrixSystem)