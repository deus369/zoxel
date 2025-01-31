void calculate_perspective_projection_matrix2(float4x4 *matrix, float left, float right, float bottom, float top, float znear, float zfar) {
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

void calculate_perspective_projection_matrix(float4x4 *matrix, const float aspect_ratio, const float camera_near_distance, const float camera_far_distance, const float fov) {
    const float znear = camera_near_distance;
    const float zfar = camera_far_distance;
    const float ymax = znear * tanf(fov * M_PI / 360.0);
    const float xmax = ymax * aspect_ratio;
    calculate_perspective_projection_matrix2(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
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
