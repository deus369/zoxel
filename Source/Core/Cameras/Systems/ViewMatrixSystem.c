//! Calculate the view matrix

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

void CalculateFrustrumMatrix(float *matrix, float left, float right, float bottom, float top, float znear, float zfar)
{
    float temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    matrix[0] = temp / temp2;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    matrix[4] = 0.0;
    matrix[5] = temp / temp3;
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    matrix[8] = (right + left) / temp2;
    matrix[9] = (top + bottom) / temp3;
    matrix[10] = (-zfar - znear) / temp4;
    matrix[11] = -1.0;
    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = (-temp * zfar) / temp4;
    matrix[15] = 0.0;
}

void CalculatePerspectiveViewMatrix(float *viewMatrix, float fovInDegrees, float aspectRatio, float znear, float zfar)
{
    if (!viewMatrix)
    {
        return;
    }
    float ymax, xmax;
    float temp, temp2, temp3, temp4;
    ymax = znear * tanf(fovInDegrees * M_PI / 360.0);
    // ymin = -ymax;
    // xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    CalculateFrustrumMatrix(viewMatrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}

//! Recalculates the View Matrix.
/**
 * This should only update when either ScreenDimensions or FieldOfView changes.
*/
void ViewMatrixSystem(ecs_iter_t *it)
{
    //printf("thing: %lu\n", it->)
    ViewMatrix *viewMatrixs = ecs_field(it, ViewMatrix, 1);
    ScreenDimensions *screenDimensions = ecs_field(it, ScreenDimensions, 2);
    FieldOfView *fieldOfViews = ecs_field(it, FieldOfView, 3);
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
        CalculatePerspectiveViewMatrix(viewMatrix->value, fieldOfView->value, aspectRatio, 1, 100);
        // printf("CalculatePerspectiveViewMatrix [%ix%i]\n", screenWidth, screenHeight);
    }
}
ECS_SYSTEM_DECLARE(ViewMatrixSystem);

//! Sets the ViewMatrix as thing.
void ViewMatrixSetSystem(ecs_iter_t *it)
{
    ViewMatrix *viewMatrixs = ecs_field(it, ViewMatrix, 1);
    for (int i = 0; i < it->count; i++)
    {
        const ViewMatrix *viewMatrix = &viewMatrixs[i];
        // set as thing
        printf("View Matrix has updated. Setting Shader View Matrix variable.\n");
        // gl_view_matrix is linked to each shader, can I have a global shader variable?
        // glUniformMatrix4fv(gl_view_matrix, 1, GL_FALSE, (const GLfloat*) viewMatrix);
    }
}
// ECS_SYSTEM_DECLARE(ViewMatrixSetSystem);