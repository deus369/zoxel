void EternalRotationSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    Rotation3D *rotations = ecs_field(it, Rotation3D, 1);
    const EternalRotation *eternalRotations = ecs_field(it, EternalRotation, 2);
    for (int i = 0; i < it->count; i++) {
        const EternalRotation *eternalRotation = &eternalRotations[i];
        Rotation3D *rotation3D = &rotations[i];
        float3 euler = quaternion_to_euler(eternalRotation->value);
        float3_multiply_float_p(&euler, delta_time);
        float4 rotate_speed = quaternion_from_euler(euler);
        rotation3D->value = quaternion_rotate(rotate_speed, rotation3D->value);
    }
}
zox_declare_system(EternalRotationSystem)