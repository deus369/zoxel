void Velocity2DSystem(iter *it) { // Veloco Rapters!
    init_delta_time()
    zox_sys_begin()
    zox_sys_in(Velocity2D)
    zox_sys_out(Position2D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Velocity2D, velocity2D)
        zox_sys_o(Position2D, position2D)
        position2D->value.x += velocity2D->value.x * delta_time;
        position2D->value.y += velocity2D->value.y * delta_time;
    }
} zoxd_system(Velocity2DSystem)
