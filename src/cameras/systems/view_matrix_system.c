// Calculates our camera to world matrix
void ViewMatrixSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(TransformMatrix)
    zox_sys_in(ProjectionMatrix)
    zox_sys_out(ViewMatrix)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TransformMatrix, transformMatrix)
        zox_sys_i(ProjectionMatrix, projectionMatrix)
        zox_sys_o(ViewMatrix, viewMatrix)
        const float4x4 view_matrix = float4x4_inverse(transformMatrix->value);
        viewMatrix->value = float4x4_multiply(view_matrix, projectionMatrix->value);
    }
} zox_declare_system(ViewMatrixSystem)