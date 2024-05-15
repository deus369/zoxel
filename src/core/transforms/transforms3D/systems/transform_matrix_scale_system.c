void TransformMatrixScaleSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(Rotation3D, rotation3Ds, 2)
    zox_field_in(Scale1D, scale1Ds, 3)
    zox_field_out(TransformMatrix, transformMatrixs, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_in(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i_in(Scale1D, scale1Ds, scale1D)
        zox_field_i_out(TransformMatrix, transformMatrixs, transformMatrix)
        // todo: why do I need to inverse rotation xyz ??
        transformMatrix->value = float4x4_transform_scale(position3D->value, float4_inverse(rotation3D->value), scale1D->value);
    }
} zox_declare_system(TransformMatrixScaleSystem)
