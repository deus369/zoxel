//! Veloco Rapters!
void Velocity2DSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    // double delta_time = (double) it->delta_time;
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    const Velocity2D *velocity2Ds = ecs_field(it, Velocity2D, 2);
    for (int i = 0; i < it->count; i++) {
        const Velocity2D *velocity2D = &velocity2Ds[i];
        Position2D *position2D = &position2Ds[i];
        position2D->value.x += velocity2D->value.x * delta_time;
        position2D->value.y += velocity2D->value.y * delta_time;
    }
} zox_declare_system(Velocity2DSystem)