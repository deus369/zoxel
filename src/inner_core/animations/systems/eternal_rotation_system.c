void EternalRotationSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_field_in(EternalRotation, eternalRotations, 2)
    zox_field_out(Rotation3D, rotation3Ds, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(EternalRotation, eternalRotations, eternalRotation)
        zox_field_i_out(Rotation3D, rotation3Ds, rotation3D)
        float3 euler = quaternion_to_euler(eternalRotation->value);
        float3_multiply_float_p(&euler, delta_time);
        const float4 rotate_speed = quaternion_from_euler(euler);
        rotation3D->value = quaternion_rotate(rotate_speed, rotation3D->value);
    }
} zox_declare_system(EternalRotationSystem)
