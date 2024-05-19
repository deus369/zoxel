// todo: why i have to reverse  rotation?? for npcs, fix this shit!
void TransformMatrixSystem(ecs_iter_t *it) {
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(Rotation3D, rotation3Ds, 2)
    zox_field_out(TransformMatrix, transformMatrixs, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_in(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i_out(TransformMatrix, transformMatrixs, transformMatrix)
        transformMatrix->value = float4x4_transform(position3D->value, rotation3D->value);
    }
} zox_declare_system(TransformMatrixSystem)
