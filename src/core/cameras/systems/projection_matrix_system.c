void calculate_perspective_projection_matrix(float4x4 *matrix, float left, float right, float bottom, float top, float znear, float zfar) {
    float temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
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

void calculate_orthographic_projection_matrix(float4x4 *matrix, float left, float right, float bottom, float top, float znear, float zfar) {
    matrix->x.x = 2.0 / (right - left);
    matrix->x.y = 0.0;
    matrix->x.z = 0.0;
    matrix->x.w = 0.0;
    matrix->y.x = 0.0;
    matrix->y.y = 2.0 / (top - bottom);
    matrix->y.z = 0.0;
    matrix->y.w = 0.0;
    matrix->z.x = 0.0;
    matrix->z.y = 0.0;
    matrix->z.z = -2.0 / (zfar - znear);
    matrix->z.w = 0.0;
    matrix->w.x = -(right + left) / (right - left);
    matrix->w.y = -(top + bottom) / (top - bottom);
    matrix->w.z = -(zfar + znear) / (zfar - znear);
    matrix->w.w = 1.0;
}

// This should only update when either ScreenDimensions or FieldOfView changes
void ProjectionMatrixSystem(ecs_iter_t *it) {
    #ifdef main_thread_projection_matrix_system
        if (!ecs_query_changed(NULL, it)) return;
    #endif
    #ifdef zox_use_orthographic_projection
        ecs_world_t *world = it->world;
    #endif
    const ScreenDimensions *screenDimensions = ecs_field(it, ScreenDimensions, 1);
    const FieldOfView *fieldOfViews = ecs_field(it, FieldOfView, 2);
    const CameraNearDistance *cameraNearDistances = ecs_field(it, CameraNearDistance, 3);
    ProjectionMatrix *projectionMatrixs = ecs_field(it, ProjectionMatrix, 4);
    // ecs_query_changed(it->query, &it, ScreenDimensions) || ecs_query_changed(q_read, &it, ScreenDimensions)
    for (int i = 0; i < it->count; i++) {
        const ScreenDimensions *screenDimensions2 = &screenDimensions[i];
        int screen_width = screenDimensions2->value.x;
        int screen_height = screenDimensions2->value.y;
        if(screen_height <= 0) continue;
        const FieldOfView *fieldOfView = &fieldOfViews[i];
        const CameraNearDistance *cameraNearDistance = &cameraNearDistances[i];
        ProjectionMatrix *projectionMatrix = &projectionMatrixs[i];
        float aspect_ratio = ((float) screen_width) / ((float) screen_height);
        float zfar = camera_far_distance;
        float znear = cameraNearDistance->value;
        float ymax = znear * tanf(fieldOfView->value * M_PI / 360.0);
        float xmax = ymax * aspect_ratio;
        #ifndef zox_use_orthographic_projection
            calculate_perspective_projection_matrix(&projectionMatrix->value, -xmax, xmax, -ymax, ymax, znear, zfar);
        #else
            if (ecs_has(world, it->entities[i], Camera2D)) {
                calculate_perspective_projection_matrix(&projectionMatrix->value, -xmax, xmax, -ymax, ymax, znear, zfar);
            } else {
                znear = 6;
                ymax = znear * tanf(fieldOfView->value * M_PI / 360.0);
                xmax = ymax * aspect_ratio;
                calculate_orthographic_projection_matrix(&projectionMatrix->value, -xmax, xmax, -ymax, ymax, znear, zfar);
            }
        #endif
    }
} zox_declare_system(ProjectionMatrixSystem)