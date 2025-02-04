void Velocity2DSystem(ecs_iter_t *it) { // Veloco Rapters!
    init_delta_time()
    zox_field_out(Position2D, position2Ds, 1)
    zox_field_in(Velocity2D, velocity2Ds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Velocity2D, velocity2Ds, velocity2D)
        zox_field_o(Position2D, position2Ds, position2D)
        position2D->value.x += velocity2D->value.x * delta_time;
        position2D->value.y += velocity2D->value.y * delta_time;
    }
} zox_declare_system(Velocity2DSystem)
