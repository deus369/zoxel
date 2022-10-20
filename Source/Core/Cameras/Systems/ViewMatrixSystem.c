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

//! Recalculates the View Matrix.
/**
 * This should only update when either ScreenDimensions or FieldOfView changes.
*/
void ViewMatrixSystem(ecs_iter_t *it)
{
    if (!ecs_query_changed(NULL, it))
    {
        // printf("A Component has not changed.\n");
        return;
    }
    ScreenDimensions *screenDimensions = ecs_field(it, ScreenDimensions, 1);
    FieldOfView *fieldOfViews = ecs_field(it, FieldOfView, 2);
    ViewMatrix *viewMatrixs = ecs_field(it, ViewMatrix, 3);
    // ecs_query_changed(it->query, &it, ScreenDimensions) || ecs_query_changed(q_read, &it, ScreenDimensions)
    for (int i = 0; i < it->count; i++)
    {
        ViewMatrix *viewMatrix = &viewMatrixs[i];
        const ScreenDimensions *screenDimensions2 = &screenDimensions[i];
        const FieldOfView *fieldOfView = &fieldOfViews[i];
        int screenWidth = screenDimensions2->value.x;
        int screenHeight = screenDimensions2->value.y;
        if(screenHeight <= 0)
        {
            return;
        }
        float aspectRatio = ((float) screenWidth) / ((float) screenHeight);
        CalculatePerspectiveViewMatrix(&viewMatrix->value, fieldOfView->value, aspectRatio, 0.1f, 100);
        // printMatrix(viewMatrix->value);
        // printf("    Perspective Updated [%ix%i]\n", screenWidth, screenHeight);
    }
}
ECS_SYSTEM_DECLARE(ViewMatrixSystem);

//! Sets the ViewMatrix as thing.
/*void ViewMatrixSetSystem(ecs_iter_t *it)
{
    ViewMatrix *viewMatrixs = ecs_field(it, ViewMatrix, 1);
    for (int i = 0; i < it->count; i++)
    {
        const ViewMatrix *viewMatrix = &viewMatrixs[i];
        // set as thing
        // printf("View Matrix has updated. Setting Shader View Matrix variable.\n");
        // gl_view_matrix is linked to each shader, can I have a global shader variable?
        // glUniformMatrix4fv(gl_view_matrix, 1, GL_FALSE, (const GLfloat*) viewMatrix);
    }
}*/
// ECS_SYSTEM_DECLARE(ViewMatrixSetSystem);