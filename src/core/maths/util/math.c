// Find more math inspiration at https://gist.github.com/mattatz/86fff4b32d198d0928d0fa4ff32cf6fa

double double_abs(double input) {
    if (input < 0) {
        return -input;
    } else {
        return input;
    }
}

float4x4 float4x4_position(float3 position) {
    float4x4 matrix = float4x4_identity();
    matrix.w.x = position.x;
    matrix.w.y = position.y;
    matrix.w.z = position.z;
    return matrix;
}

//! View Matrix multipled by projection and used to distort pixel magic.
float4x4 float4x4_view_matrix(float3 position, float3 forward, float3 up) {
    float4x4 matrix = float4x4_position(float3_multiply_float(position, -1.0f));
    float3 side = { };
    side = float3_cross(forward, up);
    side = float3_normalize(side);
    matrix.x.x = side.x;
    matrix.y.x = side.y;
    matrix.z.x = side.z;
    matrix.x.y = up.x;
    matrix.y.y = up.y;
    matrix.z.y = up.z;
    matrix.x.z = -forward.x;
    matrix.y.z = -forward.y;
    matrix.z.z = -forward.z;
    return matrix;
}

void float4x4_rotate(float4x4 *matrix, const float4 rotation) {
    matrix->x.x *= rotation.x;
    matrix->y.x *= rotation.x;
    matrix->z.x *= rotation.x;
    matrix->w.x *= rotation.x;
    matrix->x.y *= rotation.y;
    matrix->y.y *= rotation.y;
    matrix->z.y *= rotation.y;
    matrix->w.y *= rotation.y;
    matrix->x.z *= rotation.z;
    matrix->y.z *= rotation.z;
    matrix->z.z *= rotation.z;
    matrix->w.z *= rotation.z;
    matrix->x.w *= rotation.w;
    matrix->y.w *= rotation.w;
    matrix->z.w *= rotation.w;
    matrix->w.w *= rotation.w;
}

void float4_divide(float4 *input, float division) {
    input->x /= division;
    input->y /= division;
    input->z /= division;
    input->w /= division;
}