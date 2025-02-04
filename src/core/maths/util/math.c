// Find more math inspiration at https://gist.github.com/mattatz/86fff4b32d198d0928d0fa4ff32cf6fa

float4 float4_reverse(const float4 value) {
    return (float4) { -value.x, -value.y, -value.z, value.w };
}

float3 float3_reverse(const float3 value) {
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

float4x4 float4x4_position(const float3 position) {
    float4x4 matrix = float4x4_identity();
    matrix.w.x = position.x;
    matrix.w.y = position.y;
    matrix.w.z = position.z;
    return matrix;
}

float4x4 float4x4_scale(const float scale) {
    float4x4 m = float4x4_identity();
    m.x.x = scale;
    m.y.y = scale;
    m.z.z = scale;
    return m;
}

float4x4 float4x4_scale3D(const float3 scale) {
    float4x4 m = float4x4_identity();
    m.x.x = scale.x;
    m.y.y = scale.y;
    m.z.z = scale.z;
    return m;
}

float4x4 float4x4_rotation(const float4 rotation) {
    float4x4 m = float4x4_identity();
    //float x2 = rotation.x * rotation.x;
    //float y2 = rotation.y * rotation.y;
    // float z2 = rotation.z * rotation.z;
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

float4x4 float4x4_transform(const float3 position, const float4 rotation) {
    const float4x4 position_matrix = float4x4_position(position);
    const float4x4 rotation_matrix = float4x4_rotation(float4_normalize(rotation));
    return float4x4_multiply(rotation_matrix, position_matrix);
}

float4x4 float4x4_transform_scale(const float3 position, const float4 rotation, const float scale) {
    const float4x4 position_m = float4x4_position(position);
    const float4x4 rotation_m = float4x4_rotation(rotation);
    const float4x4 scale_m = float4x4_scale(scale);
    return float4x4_multiply(scale_m, float4x4_multiply(rotation_m, position_m));
}

float4x4 float4x4_transpose(const float4x4 mat) {
    float4x4 result;
    result.x = (float4) { mat.x.x, mat.y.x, mat.z.x, mat.w.x };
    result.y = (float4) { mat.x.y, mat.y.y, mat.z.y, mat.w.y };
    result.z = (float4) { mat.x.z, mat.y.z, mat.z.z, mat.w.z };
    result.w = (float4) { mat.x.w, mat.y.w, mat.z.w, mat.w.w };
    return result;
}

float3 float4x4_get_position(const float4x4 matrix) {
    return (float3) { matrix.w.x, matrix.w.y, matrix.w.z };
}

float4x4 float4x4_inverse_position(const float4x4 matrix) {
    return (float4x4) { matrix.x, matrix.y, matrix.z, (float4) { - matrix.w.x, -matrix.w.y, -matrix.w.z, matrix.w.w } };
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

float4 float4x4_multiply_float4(const float4x4 mat, const float4 point) {
    float4 result;
    result.x = mat.x.x * point.x + mat.y.x * point.y + mat.z.x * point.z + mat.w.x * point.w;
    result.y = mat.x.y * point.x + mat.y.y * point.y + mat.z.y * point.z + mat.w.y * point.w;
    result.z = mat.x.z * point.x + mat.y.z * point.y + mat.z.z * point.z + mat.w.z * point.w;
    result.w = mat.x.w * point.x + mat.y.w * point.y + mat.z.w * point.z + mat.w.w * point.w;
    return result;
}

float3 float4x4_multiply_float3_without_translation(const float4x4 mat, const float3 point) {
    float3 result;
    result.x = mat.x.x * point.x + mat.y.x * point.y + mat.z.x * point.z;
    result.y = mat.x.y * point.x + mat.y.y * point.y + mat.z.y * point.z;
    result.z = mat.x.z * point.x + mat.y.z * point.y + mat.z.z * point.z;
    return result;
}


/*float calculate_determinant(const float4x4 matrix) {
    return matrix.x.x * (matrix.y.y * (matrix.z.z * matrix.w.w - matrix.z.w * matrix.w.z) - matrix.y.z * (matrix.z.y * matrix.w.w - matrix.z.w * matrix.w.y) + matrix.y.w * (matrix.z.y * matrix.w.z - matrix.z.z * matrix.w.y)) - matrix.x.y * (matrix.y.x * (matrix.z.z * matrix.w.w - matrix.z.w * matrix.w.z) - matrix.y.z * (matrix.z.x * matrix.w.w - matrix.z.w * matrix.w.x) + matrix.y.w * (matrix.z.x * matrix.w.z - matrix.z.z * matrix.w.x)) + matrix.x.z * (matrix.y.x * (matrix.z.y * matrix.w.w - matrix.z.w * matrix.w.y) - matrix.y.y * (matrix.z.x * matrix.w.w - matrix.z.w * matrix.w.x) + matrix.y.w * (matrix.z.x * matrix.w.y - matrix.z.y * matrix.w.x)) - matrix.x.w * (matrix.y.x * (matrix.z.y * matrix.w.z - matrix.z.z * matrix.w.y) - matrix.y.y * (matrix.z.x * matrix.w.z - matrix.z.z * matrix.w.x) + matrix.y.z * (matrix.z.x * matrix.w.y - matrix.z.y * matrix.w.x));
}*/

// uses part inversion, part Gauss-Jordan elimination for position part of matrix
/*float4x4 float4x4_inverse_precise(const float4x4 matrix) {
    float4x4 inversed;
    inversed.x.x = matrix.x.x;
    inversed.x.y = matrix.y.x;
    inversed.x.z = matrix.z.x;
    inversed.x.w = 0.0f;
    inversed.y.x = matrix.x.y;
    inversed.y.y = matrix.y.y;
    inversed.y.z = matrix.z.y;
    inversed.y.w = 0.0f;
    inversed.z.x = matrix.x.z;
    inversed.z.y = matrix.y.z;
    inversed.z.z = matrix.z.z;
    inversed.z.w = 0.0f;
    const float determinant = calculate_determinant(matrix);
    // If the determinant is zero, the matrix is not invertible
    if (determinant == 0) return inversed;
    // Calculate the inverse using Gauss-Jordan elimination
    const float inverted_determinant = 1.0f / determinant;
    inversed.w.x = (-matrix.y.x * (matrix.z.y * matrix.w.z - matrix.z.z * matrix.w.y) + matrix.y.y * (matrix.z.x * matrix.w.z - matrix.z.z * matrix.w.x) - matrix.y.z * (matrix.z.x * matrix.w.y - matrix.z.y * matrix.w.x)) * inverted_determinant;
    inversed.w.y = (matrix.x.x * (matrix.z.y * matrix.w.z - matrix.z.z * matrix.w.y) - matrix.x.y * (matrix.z.x * matrix.w.z - matrix.z.z * matrix.w.x) + matrix.x.z * (matrix.z.x * matrix.w.y - matrix.z.y * matrix.w.x)) * inverted_determinant;
    inversed.w.z = (-matrix.x.x * (matrix.y.y * matrix.w.z - matrix.y.z * matrix.w.y) + matrix.x.y * (matrix.y.x * matrix.w.z - matrix.y.z * matrix.w.x) - matrix.x.z * (matrix.y.x * matrix.w.y - matrix.y.y * matrix.w.x)) * inverted_determinant;
    inversed.w.w = (matrix.x.x * (matrix.y.y * matrix.z.z - matrix.y.z * matrix.z.y) - matrix.x.y * (matrix.y.x * matrix.z.z - matrix.y.z * matrix.z.x) + matrix.x.z * (matrix.y.x * matrix.z.y - matrix.y.y * matrix.z.x)) * inverted_determinant;
    return inversed;
}*/



// Function to compute the inverse of a float4x4 matrix
/*float4x4 float4x4_inverse2(const float4x4 matrix) {
    float4x4 inv = float4x4_identity();

    // Calculate the determinant of the matrix
    float det = calculate_determinant(matrix);

    // If the determinant is zero, the matrix is not invertible
    if (det == 0.0f) {
        // Handle error or return an identity matrix
        zox_log("Matrix is not invertible!\n")
        return inv;
    }

    // Calculate the inverse using Gauss-Jordan elimination
    float invDet = 1.0f / det;

    inv.x.x = (matrix.y.y * (matrix.z.z * matrix.w.w - matrix.z.w * matrix.w.z) - matrix.y.z * (matrix.z.y * matrix.w.w - matrix.z.w * matrix.w.y) + matrix.y.w * (matrix.z.y * matrix.w.z - matrix.z.z * matrix.w.y)) * invDet;
    inv.x.y = (-matrix.x.y * (matrix.z.z * matrix.w.w - matrix.z.w * matrix.w.z) + matrix.x.z * (matrix.z.y * matrix.w.w - matrix.z.w * matrix.w.y) - matrix.x.w * (matrix.z.y * matrix.w.z - matrix.z.z * matrix.w.y)) * invDet;
    inv.x.z = (matrix.x.y * (matrix.y.z * matrix.w.w - matrix.y.w * matrix.w.z) - matrix.x.z * (matrix.y.y * matrix.w.w - matrix.y.w * matrix.w.y) + matrix.x.w * (matrix.y.y * matrix.w.z - matrix.y.z * matrix.w.y)) * invDet;
    inv.x.w = (-matrix.x.y * (matrix.y.z * matrix.z.w - matrix.y.w * matrix.z.z) + matrix.x.z * (matrix.y.y * matrix.z.w - matrix.y.z * matrix.z.y) - matrix.x.w * (matrix.y.y * matrix.z.z - matrix.y.z * matrix.z.y)) * invDet;

    inv.y.x = (-matrix.y.x * (matrix.z.z * matrix.w.w - matrix.z.w * matrix.w.z) + matrix.y.z * (matrix.z.x * matrix.w.w - matrix.z.w * matrix.w.x) - matrix.y.w * (matrix.z.x * matrix.w.z - matrix.z.z * matrix.w.x)) * invDet;
    inv.y.y = (matrix.x.x * (matrix.z.z * matrix.w.w - matrix.z.w * matrix.w.z) - matrix.x.z * (matrix.z.x * matrix.w.w - matrix.z.w * matrix.w.x) + matrix.x.w * (matrix.z.x * matrix.w.z - matrix.z.z * matrix.w.x)) * invDet;
    inv.y.z = (-matrix.x.x * (matrix.y.z * matrix.w.w - matrix.y.w * matrix.w.z) + matrix.x.z * (matrix.y.x * matrix.w.w - matrix.y.w * matrix.w.x) - matrix.x.w * (matrix.y.x * matrix.w.z - matrix.y.z * matrix.w.x)) * invDet;
    inv.y.w = (matrix.x.x * (matrix.y.z * matrix.z.w - matrix.y.w * matrix.z.z) - matrix.x.z * (matrix.y.x * matrix.z.w - matrix.y.z * matrix.z.x) + matrix.x.w * (matrix.y.x * matrix.z.z - matrix.y.z * matrix.z.x)) * invDet;

    inv.z.x = (matrix.y.x * (matrix.z.y * matrix.w.w - matrix.z.w * matrix.w.y) - matrix.y.y * (matrix.z.x * matrix.w.w - matrix.z.w * matrix.w.x) + matrix.y.w * (matrix.z.x * matrix.w.y - matrix.z.y * matrix.w.x)) * invDet;
    inv.z.y = (-matrix.x.x * (matrix.z.y * matrix.w.w - matrix.z.w * matrix.w.y) + matrix.x.y * (matrix.z.x * matrix.w.w - matrix.z.w * matrix.w.x) - matrix.x.w * (matrix.z.x * matrix.w.y - matrix.z.y * matrix.w.x)) * invDet;
    inv.z.z = (matrix.x.x * (matrix.y.y * matrix.w.w - matrix.y.w * matrix.w.y) - matrix.x.y * (matrix.y.x * matrix.w.w - matrix.y.w * matrix.w.x) + matrix.x.w * (matrix.y.x * matrix.w.y - matrix.y.y * matrix.w.x)) * invDet;
    inv.z.w = (-matrix.x.x * (matrix.y.y * matrix.z.w - matrix.y.w * matrix.z.y) + matrix.x.y * (matrix.y.x * matrix.z.w - matrix.y.z * matrix.z.x) - matrix.x.w * (matrix.y.x * matrix.z.y - matrix.y.y * matrix.z.x)) * invDet;

    inv.w.x = (-matrix.y.x * (matrix.z.y * matrix.w.z - matrix.z.z * matrix.w.y) + matrix.y.y * (matrix.z.x * matrix.w.z - matrix.z.z * matrix.w.x) - matrix.y.z * (matrix.z.x * matrix.w.y - matrix.z.y * matrix.w.x)) * invDet;
    inv.w.y = (matrix.x.x * (matrix.z.y * matrix.w.z - matrix.z.z * matrix.w.y) - matrix.x.y * (matrix.z.x * matrix.w.z - matrix.z.z * matrix.w.x) + matrix.x.z * (matrix.z.x * matrix.w.y - matrix.z.y * matrix.w.x)) * invDet;
    inv.w.z = (-matrix.x.x * (matrix.y.y * matrix.w.z - matrix.y.z * matrix.w.y) + matrix.x.y * (matrix.y.x * matrix.w.z - matrix.y.z * matrix.w.x) - matrix.x.z * (matrix.y.x * matrix.w.y - matrix.y.y * matrix.w.x)) * invDet;
    inv.w.w = (matrix.x.x * (matrix.y.y * matrix.z.z - matrix.y.z * matrix.z.y) - matrix.x.y * (matrix.y.x * matrix.z.z - matrix.y.z * matrix.z.x) + matrix.x.z * (matrix.y.x * matrix.z.y - matrix.y.y * matrix.z.x)) * invDet;

    return inv;
}*/

// this rotates the scene around the camera's location, using reverse operations
/*float4x4 float4x4_transform_camera3(const float3 position, const float4 rotation) {
    const float4x4 transform = float4x4_transform(position, rotation);
    const float4x4 inversed = float4x4_inverse(transform);
    return inversed;
}

float4x4 float4x4_transform_camera2(const float3 position, const float4 rotation) {
    const float4x4 rotation_matrix = float4x4_rotation(float4_reverse(rotation));
    const float4x4 position_matrix = float4x4_position(float3_reverse(position));
    return float4x4_multiply(position_matrix, rotation_matrix);
}*/
