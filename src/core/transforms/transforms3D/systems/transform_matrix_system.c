void TransformMatrixSystem(ecs_iter_t *it) {
    // todo: change query here
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(Rotation3D, rotation3Ds, 2)
    zox_field_out(TransformMatrix, transformMatrixs, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_in(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i_out(TransformMatrix, transformMatrixs, transformMatrix)
        const float4x4 position_matrix = float4x4_position(position3D->value);
        const float4x4 rotation_matrix = float4x4_rotation(rotation3D->value);
        transformMatrix->value = float4x4_multiply(position_matrix, rotation_matrix);
    }
} zox_declare_system(TransformMatrixSystem)
