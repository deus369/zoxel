// Find more math inspiration at https://gist.github.com/mattatz/86fff4b32d198d0928d0fa4ff32cf6fa

static inline float4 float4_reverse(const float4 value) {
    return (float4) { -value.x, -value.y, -value.z, value.w };
}

static inline float3 float3_reverse(const float3 value) {
    return (float3) { -value.x, -value.y, -value.z };
}

float4x4 float4x4_inverse(const float4x4 matrix) {
    float4x4 inv = float4x4_identity(); // Initialize the result matrix with the identity matrix

    float* inv_ptr = (float*)&inv;
    float* matrix_ptr = (float*)&matrix;

    for (int i = 0; i < 4; i++) {
        int pivot_row = i;
        float max_val = fabsf(matrix_ptr[i * 4 + i]);
        for (int j = i + 1; j < 4; j++) {
            float val = fabsf(matrix_ptr[j * 4 + i]);
            if (val > max_val) {
                max_val = val;
                pivot_row = j;
            }
        }

        if (pivot_row != i) {
            // Swap rows in both the matrix and the result matrix
            for (int k = 0; k < 4; k++) {
                float temp = matrix_ptr[i * 4 + k];
                matrix_ptr[i * 4 + k] = matrix_ptr[pivot_row * 4 + k];
                matrix_ptr[pivot_row * 4 + k] = temp;

                temp = inv_ptr[i * 4 + k];
                inv_ptr[i * 4 + k] = inv_ptr[pivot_row * 4 + k];
                inv_ptr[pivot_row * 4 + k] = temp;
            }
        }

        // Divide the pivot row by the pivot element
        float pivot_element = matrix_ptr[i * 4 + i];
        for (int k = 0; k < 4; k++) {
            matrix_ptr[i * 4 + k] /= pivot_element;
            inv_ptr[i * 4 + k] /= pivot_element;
        }

        // Subtract multiples of the pivot row from other rows
        for (int j = 0; j < 4; j++) {
            if (j != i) {
                float factor = matrix_ptr[j * 4 + i];
                for (int k = 0; k < 4; k++) {
                    matrix_ptr[j * 4 + k] -= factor * matrix_ptr[i * 4 + k];
                    inv_ptr[j * 4 + k] -= factor * inv_ptr[i * 4 + k];
                }
            }
        }
    }

    return inv;
}

static inline float4x4 float4x4_position(const float3 position) {
    float4x4 matrix = float4x4_identity();
    matrix.w.x = position.x;
    matrix.w.y = position.y;
    matrix.w.z = position.z;
    return matrix;
}

static inline float4x4 float4x4_scale(const float scale) {
    float4x4 m = float4x4_identity();
    m.x.x = scale;
    m.y.y = scale;
    m.z.z = scale;
    return m;
}

static inline float4x4 float4x4_scale3D(const float3 scale) {
    float4x4 m = float4x4_identity();
    m.x.x = scale.x;
    m.y.y = scale.y;
    m.z.z = scale.z;
    return m;
}

static inline float4x4 float4x4_rotation(const float4 rotation) {
    float4x4 m = float4x4_identity();
    float xx = 2.0 * rotation.x * rotation.x;
    float xy = 2.0 * rotation.x * rotation.y;
    float xz = 2.0 * rotation.x * rotation.z;
    float yy = 2.0 * rotation.y * rotation.y;
    float yz = 2.0 * rotation.y * rotation.z;
    float zz = 2.0 * rotation.z * rotation.z;
    float wx = 2.0 * rotation.w * rotation.x;
    float wy = 2.0 * rotation.w * rotation.y;
    float wz = 2.0 * rotation.w * rotation.z;
    m.x.x = (1.0 - yy - zz);
    m.x.y = (xy + wz);
    m.x.z = (xz - wy);
    m.y.x = (xy - wz);
    m.y.y = (1.0 - xx - zz);
    m.y.z = (yz + wx);
    m.z.x = (xz + wy);
    m.z.y = (yz - wx);
    m.z.z = (1.0 - xx - yy);
    return m;
}

static inline float4x4 float4x4_transform(const float3 position, const float4 rotation) {
    const float4x4 position_matrix = float4x4_position(position);
    const float4x4 rotation_matrix = float4x4_rotation(float4_normalize(rotation));
    return float4x4_multiply(rotation_matrix, position_matrix);
}

static inline float4x4 float4x4_transform_scale(const float3 position, const float4 rotation, const float scale) {
    const float4x4 position_m = float4x4_position(position);
    const float4x4 rotation_m = float4x4_rotation(rotation);
    const float4x4 scale_m = float4x4_scale(scale);
    return float4x4_multiply(scale_m, float4x4_multiply(rotation_m, position_m));
}

static inline float4x4 float4x4_transpose(const float4x4 mat) {
    float4x4 result;
    result.x = (float4) { mat.x.x, mat.y.x, mat.z.x, mat.w.x };
    result.y = (float4) { mat.x.y, mat.y.y, mat.z.y, mat.w.y };
    result.z = (float4) { mat.x.z, mat.y.z, mat.z.z, mat.w.z };
    result.w = (float4) { mat.x.w, mat.y.w, mat.z.w, mat.w.w };
    return result;
}

static inline float3 float4x4_get_position(const float4x4 matrix) {
    return (float3) { matrix.w.x, matrix.w.y, matrix.w.z };
}

static inline float4x4 float4x4_inverse_position(const float4x4 matrix) {
    return (float4x4) { matrix.x, matrix.y, matrix.z, (float4) { - matrix.w.x, -matrix.w.y, -matrix.w.z, matrix.w.w } };
}

//! View Matrix multipled by projection and used to distort pixel magic.
static inline float4x4 float4x4_view_matrix(const float3 position, const float3 forward, const float3 up) {
    float4x4 matrix = float4x4_position(float3_scale(position, -1.0f));
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

static inline void float4x4_rotate(float4x4 *matrix, const float4 rotation) {
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

static inline void float4_divide(float4 *input, const float division) {
    input->x /= division;
    input->y /= division;
    input->z /= division;
    input->w /= division;
}

static inline float3 float4x4_multiply_float3(const float4x4 mat, const float3 point) {
    float3 result;
    result.x = mat.x.x * point.x + mat.y.x * point.y + mat.z.x * point.z + mat.w.x;
    result.y = mat.x.y * point.x + mat.y.y * point.y + mat.z.y * point.z + mat.w.y;
    result.z = mat.x.z * point.x + mat.y.z * point.y + mat.z.z * point.z + mat.w.z;
    return result;
}

static inline float4 float4x4_multiply_float4(const float4x4 mat, const float4 point) {
    float4 result;
    result.x = mat.x.x * point.x + mat.y.x * point.y + mat.z.x * point.z + mat.w.x * point.w;
    result.y = mat.x.y * point.x + mat.y.y * point.y + mat.z.y * point.z + mat.w.y * point.w;
    result.z = mat.x.z * point.x + mat.y.z * point.y + mat.z.z * point.z + mat.w.z * point.w;
    result.w = mat.x.w * point.x + mat.y.w * point.y + mat.z.w * point.z + mat.w.w * point.w;
    return result;
}

static inline float3 float4x4_multiply_float3_without_translation(const float4x4 mat, const float3 point) {
    float3 result;
    result.x = mat.x.x * point.x + mat.y.x * point.y + mat.z.x * point.z;
    result.y = mat.x.y * point.x + mat.y.y * point.y + mat.z.y * point.z;
    result.z = mat.x.z * point.x + mat.y.z * point.y + mat.z.z * point.z;
    return result;
}