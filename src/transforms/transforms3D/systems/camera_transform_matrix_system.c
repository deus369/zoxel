// remember: camera operations are opposite as it rotates scene around it, we cannot use its transform for non camera things, its just  used for getting  view matrix!
/*void CameraTransformMatrixSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(Rotation3D, rotation3Ds, 2)
    zox_field_out(TransformMatrix, transformMatrixs, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_i(Rotation3D, rotation3Ds, rotation3D)
        zox_field_o(TransformMatrix, transformMatrixs, transformMatrix)
        transformMatrix->value = float4x4_transform_camera(position3D->value, rotation3D->value);
    }
} zox_declare_system(CameraTransformMatrixSystem)*/
