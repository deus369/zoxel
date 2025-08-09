// todo: why i have to reverse  rotation?? for npcs, fix this shit!
void TransformMatrixSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(Position3D)
    zox_sys_in(Rotation3D)
    zox_sys_out(TransformMatrix)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Position3D, position3D)
        zox_sys_i(Rotation3D, rotation3D)
        zox_sys_o(TransformMatrix, transformMatrix)
        transformMatrix->value = float4x4_transform(position3D->value, rotation3D->value);
    }
} zoxd_system(TransformMatrixSystem)