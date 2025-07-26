void EternalRotationSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_sys_begin()
    zox_sys_in(EternalRotation)
    zox_sys_out(Rotation3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(EternalRotation, eternalRotation)
        zox_sys_o(Rotation3D, rotation3D)
        float3 euler = quaternion_to_euler(eternalRotation->value);
        float3_scale_p(&euler, delta_time);
        const float4 rotate_speed = quaternion_from_euler(euler);
        rotation3D->value = quaternion_rotate(rotate_speed, rotation3D->value);
        // zox_log("   - eternally rotating: %s\n", zox_get_name(it->entities[i]))
    }
} zox_declare_system(EternalRotationSystem)
