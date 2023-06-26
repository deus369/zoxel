const unsigned char physics_disable_frames = 8;

void Physics3DDisableSystem(ecs_iter_t *it) {
    #ifdef zoxel_disable_velocity
        return;
    #endif
    double delta_time = zox_delta_time;
    InitializePhysics3D *initializePhysics3Ds = ecs_field(it, InitializePhysics3D, 1);
    Position3D *position3Ds = ecs_field(it, Position3D, 2);
    Velocity3D *velocity3Ds = ecs_field(it, Velocity3D, 3);
    for (int i = 0; i < it->count; i++) {
        InitializePhysics3D *initializePhysics3D = &initializePhysics3Ds[i];
        if (initializePhysics3D->value < physics_disable_frames) {
            initializePhysics3D->value++;
            Position3D *position3D = &position3Ds[i];
            Velocity3D *velocity3D = &velocity3Ds[i];
            position3D->value.x -= velocity3D->value.x * delta_time;
            position3D->value.y -= velocity3D->value.y * delta_time;
            position3D->value.z -= velocity3D->value.z * delta_time;
            velocity3D->value.x = 0;
            velocity3D->value.y = 0;
            velocity3D->value.z = 0;
            // zoxel_log("disabling physics 3D [%lu]\n", it->entities[i]);
        }
    }
} zox_declare_system(Physics3DDisableSystem)

