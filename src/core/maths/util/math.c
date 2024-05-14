// Find more math inspiration at https://gist.github.com/mattatz/86fff4b32d198d0928d0fa4ff32cf6fa

double double_abs(const double input) {
    if (input < 0) return -input;
    else return input;
}

float4x4 float4x4_position(const float3 position) {
    float4x4 matrix = float4x4_identity();
    matrix.w.x = position.x;
    matrix.w.y = position.y;
    matrix.w.z = position.z;
    return matrix;
}

float3 float4x4_get_position(const float4x4 matrix) {
    return (float3) { matrix.w.x, matrix.w.y, matrix.w.z };
}

// this just reversed position tho?
float4x4 float4x4_inverse_position(const float4x4 matrix) {
    return (float4x4) { matrix.x, matrix.y, matrix.z, (float4) { - matrix.w.x, -matrix.w.y, -matrix.w.z, matrix.w.w } };
}

// Function to compute the inverse of a float4x4 matrix
float4x4 float4x4_inverse(const float4x4 matrix) {
    float4x4 inv;
    float determinant = matrix.x.x * (matrix.y.y * matrix.z.z * matrix.w.w - matrix.y.z * matrix.z.y * matrix.w.w + matrix.y.w * matrix.z.y * matrix.w.z - matrix.y.w * matrix.z.z * matrix.w.y) -
                        matrix.x.y * (matrix.y.x * matrix.z.z * matrix.w.w - matrix.y.z * matrix.z.x * matrix.w.w + matrix.y.w * matrix.z.x * matrix.w.z - matrix.y.w * matrix.z.z * matrix.w.x) +
                        matrix.x.z * (matrix.y.x * matrix.z.y * matrix.w.w - matrix.y.y * matrix.z.x * matrix.w.w + matrix.y.w * matrix.z.x * matrix.w.y - matrix.y.w * matrix.z.y * matrix.w.x) -
                        matrix.x.w * (matrix.y.x * matrix.z.y * matrix.w.z - matrix.y.y * matrix.z.x * matrix.w.z + matrix.y.z * matrix.z.x * matrix.w.y - matrix.y.z * matrix.z.y * matrix.w.x);

    if (determinant == 0.0f) {
        // Matrix is not invertible, handle error or return an identity matrix
        return float4x4_identity();
    }

    inv.x.x = (matrix.y.y * matrix.z.z * matrix.w.w - matrix.y.z * matrix.z.y * matrix.w.w + matrix.y.w * matrix.z.y * matrix.w.z - matrix.y.w * matrix.z.z * matrix.w.y) / determinant;
    inv.x.y = (-matrix.x.y * matrix.z.z * matrix.w.w + matrix.x.z * matrix.z.y * matrix.w.w - matrix.x.w * matrix.z.y * matrix.w.z + matrix.x.w * matrix.z.z * matrix.w.y) / determinant;
    inv.x.z = (matrix.x.y * matrix.y.z * matrix.w.w - matrix.x.z * matrix.y.y * matrix.w.w + matrix.x.w * matrix.y.y * matrix.w.z - matrix.x.w * matrix.y.z * matrix.w.y) / determinant;
    inv.x.w = (-matrix.x.y * matrix.y.z * matrix.z.w + matrix.x.z * matrix.y.y * matrix.z.w - matrix.x.w * matrix.y.y * matrix.z.z + matrix.x.w * matrix.y.z * matrix.z.y) / determinant;

    inv.y.x = (-matrix.y.x * matrix.z.z * matrix.w.w + matrix.y.z * matrix.z.x * matrix.w.w - matrix.y.w * matrix.z.x * matrix.w.z + matrix.y.w * matrix.z.z * matrix.w.x) / determinant;
    inv.y.y = (matrix.x.x * matrix.z.z * matrix.w.w - matrix.x.z * matrix.z.x * matrix.w.w + matrix.x.w * matrix.z.x * matrix.w.z - matrix.x.w * matrix.z.z * matrix.w.x) / determinant;
    inv.y.z = (-matrix.x.x * matrix.y.z * matrix.w.w + matrix.x.z * matrix.y.x * matrix.w.w - matrix.x.w * matrix.y.x * matrix.w.z + matrix.x.w * matrix.y.z * matrix.w.x) / determinant;
    inv.y.w = (matrix.x.x * matrix.y.z * matrix.z.w - matrix.x.z * matrix.y.x * matrix.z.w + matrix.x.w * matrix.y.x * matrix.z.z - matrix.x.w * matrix.y.z * matrix.z.x) / determinant;

    inv.z.x = (matrix.y.x * matrix.z.y * matrix.w.w - matrix.y.y * matrix.z.x * matrix.w.w + matrix.y.w * matrix.z.x * matrix.w.y - matrix.y.w * matrix.z.y * matrix.w.x) / determinant;
    inv.z.y = (-matrix.x.x * matrix.z.y * matrix.w.w + matrix.x.y * matrix.z.x * matrix.w.w - matrix.x.w * matrix.z.x * matrix.w.y + matrix.x.w * matrix.z.y * matrix.w.x) / determinant;
    inv.z.z = (matrix.x.x * matrix.y.y * matrix.w.w - matrix.x.y * matrix.y.x * matrix.w.w + matrix.x.w * matrix.y.x * matrix.w.y - matrix.x.w * matrix.y.y * matrix.w.x) / determinant;
    inv.z.w = (-matrix.x.x * matrix.y.y * matrix.z.w + matrix.x.y * matrix.y.x * matrix.z.w - matrix.x.w * matrix.y.x * matrix.z.y + matrix.x.w * matrix.y.y * matrix.z.x) / determinant;

    inv.w.x = (-matrix.y.x * matrix.z.y * matrix.w.z + matrix.y.y * matrix.z.x * matrix.w.z - matrix.y.z * matrix.z.x * matrix.w.y + matrix.y.z * matrix.z.y * matrix.w.x) / determinant;
    inv.w.y = (matrix.x.x * matrix.z.y * matrix.w.z - matrix.x.y * matrix.z.x * matrix.w.z + matrix.x.z * matrix.z.x * matrix.w.y - matrix.x.z * matrix.z.y * matrix.w.x) / determinant;
    inv.w.z = (-matrix.x.x * matrix.y.y * matrix.w.z + matrix.x.y * matrix.y.x * matrix.w.z - matrix.x.z * matrix.y.x * matrix.w.y + matrix.x.z * matrix.y.y * matrix.w.x) / determinant;
    inv.w.w = (matrix.x.x * matrix.y.y * matrix.z.z - matrix.x.y * matrix.y.x * matrix.z.z + matrix.x.z * matrix.y.x * matrix.z.y - matrix.x.z * matrix.y.y * matrix.z.x) / determinant;

    return inv;
}

float4x4 float4x4_rotation(const float4 rotation) {
    float4x4 m = float4x4_identity();
    float x = rotation.x;
    float y = rotation.y;
    float z = rotation.z;
    float w = rotation.w;
    float x2 = x + x;
    float y2 = y + y;
    float z2 = z + z;
    float xx = x * x2;
    float xy = x * y2;
    float xz = x * z2;
    float yy = y * y2;
    float yz = y * z2;
    float zz = z * z2;
    float wx = w * x2;
    float wy = w * y2;
    float wz = w * z2;
    m.x.x = 1.0 - (yy + zz);
    m.x.y = xy - wz;
    m.x.z = xz + wy;
    m.y.x = xy + wz;
    m.y.y = 1.0 - (xx + zz);
    m.y.z = yz - wx;
    m.z.x = xz - wy;
    m.z.y = yz + wx;
    m.z.z = 1.0 - (xx + yy);
    m.w.w = 1.0;
    return m;
}

//! View Matrix multipled by projection and used to distort pixel magic.
float4x4 float4x4_view_matrix(const float3 position, const float3 forward, const float3 up) {
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

void float4_divide(float4 *input, const float division) {
    input->x /= division;
    input->y /= division;
    input->z /= division;
    input->w /= division;
}

float3 float4x4_multiply_float3(const float4x4 mat, const float3 point) {
    float3 result;
    result.x = mat.x.x * point.x + mat.y.x * point.y + mat.z.x * point.z + mat.w.x;
    result.y = mat.x.y * point.x + mat.y.y * point.y + mat.z.y * point.z + mat.w.y;
    result.z = mat.x.z * point.x + mat.y.z * point.y + mat.z.z * point.z + mat.w.z;
    return result;
}



float4x4 float4x4_transform(const float3 position, const float4 rotation) {
    float4x4 m;
    // Compute rotation matrix
    float x2 = rotation.x + rotation.x;
    float y2 = rotation.y + rotation.y;
    float z2 = rotation.z + rotation.z;
    float xx = rotation.x * x2;
    float xy = rotation.x * y2;
    float xz = rotation.x * z2;
    float yy = rotation.y * y2;
    float yz = rotation.y * z2;
    float zz = rotation.z * z2;
    float wx = rotation.w * x2;
    float wy = rotation.w * y2;
    float wz = rotation.w * z2;
    m.x.x = 1.0 - (yy + zz);
    m.x.y = xy - wz;
    m.x.z = xz + wy;
    m.x.w = 0.0;
    m.y.x = xy + wz;
    m.y.y = 1.0 - (xx + zz);
    m.y.z = yz - wx;
    m.y.w = 0.0;
    m.z.x = xz - wy;
    m.z.y = yz + wx;
    m.z.z = 1.0 - (xx + yy);
    m.z.w = 0.0;
    m.w.x = position.x;
    m.w.y = position.y;
    m.w.z = position.z;
    m.w.w = 1.0;
    return m;
}
