void TransformMatrixScaleSystem(ecs_iter_t *it) {
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(Rotation3D, rotation3Ds, 2)
    zox_field_in(Scale1D, scale1Ds, 3)
    zox_field_out(TransformMatrix, transformMatrixs, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_i(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i(Scale1D, scale1Ds, scale1D)
        zox_field_o(TransformMatrix, transformMatrixs, transformMatrix)
        transformMatrix->value = float4x4_transform_scale(position3D->value, rotation3D->value, scale1D->value);
    }
} zox_declare_system(TransformMatrixScaleSystem)