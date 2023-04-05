//! Calculate the view matrix
void calculate_frustrum_matrix(float4x4 *matrix, float left, float right, float bottom, float top, float znear, float zfar) {
    float temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    // float* matrix2 = (float*) &matrix;
    matrix->x.x = temp / temp2;
    matrix->x.y = 0.0;
    matrix->x.z = 0.0;
    matrix->x.w = 0.0;
    matrix->y.x = 0.0;
    matrix->y.y = temp / temp3;
    matrix->y.z = 0.0;
    matrix->y.w = 0.0;
    matrix->z.x = (right + left) / temp2;
    matrix->z.y = (top + bottom) / temp3;
    matrix->z.z = (-zfar - znear) / temp4;
    matrix->z.w = -1.0;
    matrix->w.x = 0.0;
    matrix->w.y = 0.0;
    matrix->w.z = (-temp * zfar) / temp4;
    matrix->w.w = 0.0;
}

// This should only update when either ScreenDimensions or FieldOfView changes
void ProjectionMatrixSystem(ecs_iter_t *it) {
    #ifdef main_thread_projection_matrix_system
        if (!ecs_query_changed(NULL, it)) {  // this doesn't work in multithreaded
            // printf("A Component has not changed.\n");
            return;
        }
    #endif
    // printf("ProjectionMatrixSystem Updated\n");
    const ScreenDimensions *screenDimensions = ecs_field(it, ScreenDimensions, 1);
    const FieldOfView *fieldOfViews = ecs_field(it, FieldOfView, 2);
    const CameraNearDistance *cameraNearDistances = ecs_field(it, CameraNearDistance, 3);
    ProjectionMatrix *projectionMatrixs = ecs_field(it, ProjectionMatrix, 4);
    // ecs_query_changed(it->query, &it, ScreenDimensions) || ecs_query_changed(q_read, &it, ScreenDimensions)
    for (int i = 0; i < it->count; i++) {
        const ScreenDimensions *screenDimensions2 = &screenDimensions[i];
        int screenWidth = screenDimensions2->value.x;
        int screenHeight = screenDimensions2->value.y;
        if(screenHeight <= 0) {
            continue;
        }
        const FieldOfView *fieldOfView = &fieldOfViews[i];
        const CameraNearDistance *cameraNearDistance = &cameraNearDistances[i];
        ProjectionMatrix *projectionMatrix = &projectionMatrixs[i];
        float znear = cameraNearDistance->value;
        float zfar = camera_far_distance;
        float aspect_ratio = ((float) screenWidth) / ((float) screenHeight);
        float ymax = znear * tanf(fieldOfView->value * M_PI / 360.0);
        float xmax = ymax * aspect_ratio;
        calculate_frustrum_matrix(&projectionMatrix->value, -xmax, xmax, -ymax, ymax, znear, zfar);
        // float4x4_print(view_matrix->value);
        // printf("    Perspective Updated [%ix%i]\n", screenWidth, screenHeight);
    }
}
zoxel_declare_system(ProjectionMatrixSystem)