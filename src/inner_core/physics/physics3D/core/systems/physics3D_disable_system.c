const unsigned char physics_disable_frames = 8;

void Physics3DDisableSystem(ecs_iter_t *it) {
#ifdef zoxel_disable_velocity
    return;
#endif
    init_delta_time()
    zox_field_out(InitializePhysics3D, initializePhysics3Ds, 1)
    zox_field_out(Position3D, position3Ds, 2)
    zox_field_out(Velocity3D, velocity3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(InitializePhysics3D, initializePhysics3Ds, initializePhysics3D)
        if (initializePhysics3D->value < physics_disable_frames) {
            initializePhysics3D->value++;
            zox_field_i_out(Position3D, position3Ds, position3D)
            zox_field_i_out(Velocity3D, velocity3Ds, velocity3D)
            position3D->value.x -= velocity3D->value.x * delta_time;
            position3D->value.y -= velocity3D->value.y * delta_time;
            position3D->value.z -= velocity3D->value.z * delta_time;
            float3_make_zero(&velocity3D->value);
        }
    }
} zox_declare_system(Physics3DDisableSystem)

