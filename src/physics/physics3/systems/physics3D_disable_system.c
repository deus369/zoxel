const byte physics_disable_frames = 8;

void Physics3DDisableSystem(iter *it) {
#ifdef zoxel_disable_velocity
    return;
#endif
    init_delta_time()
    zox_sys_begin()
    zox_sys_out(InitializePhysics3D)
    zox_sys_out(Position3D)
    zox_sys_out(Velocity3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(InitializePhysics3D, initializePhysics3D)
        zox_sys_o(Position3D, position3D)
        zox_sys_o(Velocity3D, velocity3D)
        if (initializePhysics3D->value < physics_disable_frames) {
            initializePhysics3D->value++;
            position3D->value.x -= velocity3D->value.x * delta_time;
            position3D->value.y -= velocity3D->value.y * delta_time;
            position3D->value.z -= velocity3D->value.z * delta_time;
            float3_make_zero(&velocity3D->value);
        }
    }
} zox_declare_system(Physics3DDisableSystem)

