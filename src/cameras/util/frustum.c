void calculate_frustum_corners_d3(const float4x4 view_projection_matrix, double3 *frustum) {
    const float4x4 inverse_view_projection_matrix = float4x4_inverse(view_projection_matrix);
    const float4x4 mat = inverse_view_projection_matrix;
    frustum[0] = (double3) { -1, -1, -1 };
    frustum[1] = (double3) { 1, -1, -1 };
    frustum[2] = (double3) { 1, 1, -1 };
    frustum[3] = (double3) { -1, 1, -1 };
    frustum[4] = (double3) { -1, -1, 1 };
    frustum[5] = (double3) { 1, -1, 1 };
    frustum[6] = (double3) { 1, 1, 1 };
    frustum[7] = (double3) { -1, 1, 1 };
    for (int i = 0; i < 8; i++) {
        const double4 corner = double4_from_double3(frustum[i], 1);
        const double4 world_corner = float4x4_multiply_double4(mat, corner);
        frustum[i] = double3_divide_double((double3) { world_corner.x, world_corner.y, world_corner.z }, world_corner.w);
    }
}

void calculate_frustum_corners_f3(const float4x4 view_projection_matrix, float3 *frustum) {
    const float4x4 inverse_view_projection_matrix = float4x4_inverse(view_projection_matrix);
    const float4x4 mat = inverse_view_projection_matrix;
    frustum[0] = (float3) { -1, -1, -1 };
    frustum[1] = (float3) { 1, -1, -1 };
    frustum[2] = (float3) { 1, 1, -1 };
    frustum[3] = (float3) { -1, 1, -1 };
    frustum[4] = (float3) { -1, -1, 1 };
    frustum[5] = (float3) { 1, -1, 1 };
    frustum[6] = (float3) { 1, 1, 1 };
    frustum[7] = (float3) { -1, 1, 1 };
    for (int i = 0; i < 8; i++) {
        const float4 corner = float4_from_float3(frustum[i], 1);
        const float4 world_corner = float4x4_multiply_float4(mat, corner);
        frustum[i] = float3_divide_float((float3) { world_corner.x, world_corner.y, world_corner.z }, world_corner.w);
    }
}
