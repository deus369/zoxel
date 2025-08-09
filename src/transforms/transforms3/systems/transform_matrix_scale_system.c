void TransformMatrixScaleSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(Position3D)
    zox_sys_in(Rotation3D)
    zox_sys_in(Scale1D)
    zox_sys_out(TransformMatrix)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Position3D, position3D)
        zox_sys_i(Rotation3D, rotation3D)
        zox_sys_i(Scale1D, scale1D)
        zox_sys_o(TransformMatrix, transformMatrix)
        transformMatrix->value = float4x4_transform_scale(position3D->value, rotation3D->value, scale1D->value);
    }
} zoxd_system(TransformMatrixScaleSystem)