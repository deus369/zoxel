// #define zoxel_debug_alpha3D_system
void Alpha3DSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    Alpha3D *alpha3Ds = ecs_field(it, Alpha3D, 1);
    Omega3D *omega3Ds = ecs_field(it, Omega3D, 2);
    for (int i = 0; i < it->count; i++) {
        Alpha3D *alpha3D = &alpha3Ds[i];
        if (alpha3D->value.x == 0 && alpha3D->value.y == 0 && alpha3D->value.z == 0 && alpha3D->value.w == 1) continue;
        float magnitude = quaternion_magnitude(alpha3D->value);
        if (magnitude != 0.0f) {
            Omega3D *omega3D = &omega3Ds[i];
            float4 delta_omega = get_delta_rotation(alpha3D->value, magnitude, delta_time);
            quaternion_rotate_quaternion_p(&omega3D->value, delta_omega);
            #ifdef zoxel_debug_alpha3D_system
                zoxel_log("     + post omega [%fx%fx%fx%f]\n", omega3D->value.x, omega3D->value.y, omega3D->value.z, omega3D->value.w);
            #endif
            // zoxel_log("alpha effecting omega\n");
        }
        alpha3D->value = quaternion_identity;
    }
} zox_declare_system(Alpha3DSystem)