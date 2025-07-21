void Velocity3System(ecs_iter_t *it) { //! Veloco Rapters!
    init_delta_time()
    zox_sys_begin()
    zox_sys_in(Velocity3D)
    zox_sys_out(Position3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Velocity3D, velocity)
        zox_sys_o(Position3D, position)
        position->value = float3_add(position->value, float3_scale(velocity->value, delta_time));
    }
} zox_declare_system(Velocity3System)
