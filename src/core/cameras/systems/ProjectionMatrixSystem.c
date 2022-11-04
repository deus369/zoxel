//! Calculate the view matrix

void CalculateFrustrumMatrix(float4x4 *matrix, float left, float right, float bottom, float top, float znear, float zfar)
{
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

void CalculatePerspectiveViewMatrix(float4x4 *viewMatrix, float fovInDegrees, float aspectRatio, float znear, float zfar)
{
    float ymax, xmax;
    ymax = znear * tanf(fovInDegrees * M_PI / 360.0);
    xmax = ymax * aspectRatio;
    CalculateFrustrumMatrix(viewMatrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}

//! Recalculates the Projection Matrix.
/**
 * This should only update when either ScreenDimensions or FieldOfView changes.
*/
void ProjectionMatrixSystem(ecs_iter_t *it)
{
    if (!ecs_query_changed(NULL, it))
    {
        // printf("A Component has not changed.\n");
        return;
    }
    const ScreenDimensions *screenDimensions = ecs_field(it, ScreenDimensions, 1);
    const FieldOfView *fieldOfViews = ecs_field(it, FieldOfView, 2);
    ProjectionMatrix *projectionMatrixs = ecs_field(it, ProjectionMatrix, 3);
    // ecs_query_changed(it->query, &it, ScreenDimensions) || ecs_query_changed(q_read, &it, ScreenDimensions)
    for (int i = 0; i < it->count; i++)
    {
        const ScreenDimensions *screenDimensions2 = &screenDimensions[i];
        int screenWidth = screenDimensions2->value.x;
        int screenHeight = screenDimensions2->value.y;
        if(screenHeight <= 0)
        {
            return;
        }
        float aspectRatio = ((float) screenWidth) / ((float) screenHeight);
        const FieldOfView *fieldOfView = &fieldOfViews[i];
        ProjectionMatrix *projectionMatrix = &projectionMatrixs[i];
        CalculatePerspectiveViewMatrix(&projectionMatrix->value, fieldOfView->value, aspectRatio, 0.1f, 100);
        // float4x4_print(viewMatrix->value);
        // printf("    Perspective Updated [%ix%i]\n", screenWidth, screenHeight);
    }
}
ECS_SYSTEM_DECLARE(ProjectionMatrixSystem);