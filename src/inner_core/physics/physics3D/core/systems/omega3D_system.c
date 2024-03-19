// #define zoxel_debug_omega3D_system
void Omega3DSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    zox_field_out(Omega3D, omega3Ds, 1)
    zox_field_out(Rotation3D, rotation3Ds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Omega3D, omega3Ds, omega3D)
        if (omega3D->value.x == 0 && omega3D->value.y == 0 && omega3D->value.z == 0 && omega3D->value.w == 1) continue;
        // check if it's magnitude is close to a cutoff point and then set to identity too
        zox_field_i_out(Rotation3D, rotation3Ds, rotation3D)
#ifdef zoxel_debug_omega3D_system
        zox_log(" > omega3D [%fx%fx%fx%f]\n", omega3D->value.x, omega3D->value.y, omega3D->value.z, omega3D->value.w);
        zox_log("     + pre rotation [%fx%fx%fx%f]\n", rotation3D->value.x, rotation3D->value.y, rotation3D->value.z, rotation3D->value.w);
#endif
        float magnitude = quaternion_magnitude(omega3D->value);
        if (magnitude == 0.0f) continue;
        float4 delta_rotation = get_delta_rotation(omega3D->value, magnitude, delta_time);
        quaternion_rotate_quaternion_p(&rotation3D->value, delta_rotation);
#ifdef zoxel_debug_omega3D_system
        zox_log("     + post rotation [%fx%fx%fx%f]\n", rotation3D->value.x, rotation3D->value.y, rotation3D->value.z, rotation3D->value.w);
#endif
    }
} zox_declare_system(Omega3DSystem)
