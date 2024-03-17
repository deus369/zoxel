//  #define zoxel_debug_alpha3D_system
void Alpha3DSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    zox_field_out(Alpha3D, alpha3Ds, 1)
    zox_field_out(Omega3D, omega3Ds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(Alpha3D, alpha3Ds, alpha3D)
        if (alpha3D->value.x == 0 && alpha3D->value.y == 0 && alpha3D->value.z == 0 && alpha3D->value.w == 1) continue;
        float magnitude = quaternion_magnitude(alpha3D->value);
        if (magnitude != 0.0f) {
            zox_field_i_out(Omega3D, omega3Ds, omega3D)
            float4 delta_omega = get_delta_rotation(alpha3D->value, magnitude, delta_time);
            quaternion_rotate_quaternion_p(&omega3D->value, delta_omega);
#ifdef zoxel_debug_alpha3D_system
            zoxel_log("     + post omega [%fx%fx%fx%f]\n", omega3D->value.x, omega3D->value.y, omega3D->value.z, omega3D->value.w);
#endif
        }
        alpha3D->value = quaternion_identity;
    }
} zox_declare_system(Alpha3DSystem)
