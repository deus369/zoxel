void ViewMatrixSystem(ecs_iter_t *it) {
    // todo: change query here
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(Rotation3D, rotation3Ds, 2)
    zox_field_in(ProjectionMatrix, projectionMatrixs, 3)
    zox_field_out(ViewMatrix, viewMatrixs, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_in(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i_in(ProjectionMatrix, projectionMatrixs, projectionMatrix)
        zox_field_i_out(ViewMatrix, viewMatrixs, viewMatrix)
        const float4x4 cameraPositionMatrix = float4x4_position(float3_multiply_float(position3D->value, -1));
        const float4x4 cameraViewMatrix = float4x4_multiply(cameraPositionMatrix, quaternion_to_matrix(rotation3D->value));
        viewMatrix->value = float4x4_multiply(cameraViewMatrix, projectionMatrix->value);
    }
} zox_declare_system(ViewMatrixSystem)
