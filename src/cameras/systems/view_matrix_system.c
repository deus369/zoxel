// Calculates our camera to world matrix
void ViewMatrixSystem(ecs_iter_t *it) {
    zox_field_in(TransformMatrix, transformMatrixs, 1)
    zox_field_in(ProjectionMatrix, projectionMatrixs, 2)
    zox_field_out(ViewMatrix, viewMatrixs, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(TransformMatrix, transformMatrixs, transformMatrix)
        zox_field_i(ProjectionMatrix, projectionMatrixs, projectionMatrix)
        zox_field_o(ViewMatrix, viewMatrixs, viewMatrix)
        const float4x4 view_matrix = float4x4_inverse(transformMatrix->value);
        viewMatrix->value = float4x4_multiply(view_matrix, projectionMatrix->value);
    }
} zox_declare_system(ViewMatrixSystem)
