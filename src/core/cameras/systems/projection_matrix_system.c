// This should only update when either ScreenDimensions or FieldOfView changes
void ProjectionMatrixSystem(ecs_iter_t *it) {
#ifdef main_thread_projection_matrix_system
    if (!ecs_query_changed(NULL, it)) return;
#endif
#ifdef zox_use_orthographic_projection
    zox_iter_world()
#endif
    zox_field_in(ScreenDimensions, screenDimensionss, 1)
    zox_field_in(FieldOfView, fieldOfViews, 2)
    zox_field_in(CameraNearDistance, cameraNearDistances, 3)
    zox_field_out(ProjectionMatrix, projectionMatrixs, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ScreenDimensions, screenDimensionss, screenDimensions)
        const int screen_width = screenDimensions->value.x;
        const int screen_height = screenDimensions->value.y;
        if(screen_height <= 0) continue;
        const float aspect_ratio = ((float) screen_width) / ((float) screen_height);
        zox_field_i_in(FieldOfView, fieldOfViews, fieldOfView)
        zox_field_i_in(CameraNearDistance, cameraNearDistances, cameraNearDistance)
        zox_field_i_out(ProjectionMatrix, projectionMatrixs, projectionMatrix)
#ifndef zox_use_orthographic_projection
        calculate_perspective_projection_matrix(&projectionMatrix->value, aspect_ratio, cameraNearDistance->value, camera_far_distance, fieldOfView->value);
#else
        zox_field_e()
        if (zox_has(e, Camera2D)) {
            calculate_perspective_projection_matrix(&projectionMatrix->value, aspect_ratio, cameraNearDistance->value, camera_far_distance, fieldOfView->value);
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
} zox_declare_system(ProjectionMatrixSystem)
