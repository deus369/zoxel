//! Adds force to the velocity per frame.
void Acceleration2DSystem(ecs_iter_t *it) {
    double deltaTime = (double) it->delta_time;
    Velocity2D *velocity2Ds = ecs_field(it, Velocity2D, 1);
    Acceleration2D *acceleration2Ds = ecs_field(it, Acceleration2D, 2);
    for (int i = 0; i < it->count; i++) {
        Acceleration2D *acceleration2D = &acceleration2Ds[i];
        Velocity2D *velocity2D = &velocity2Ds[i];
        velocity2D->value.x += acceleration2D->value.x * deltaTime;
        velocity2D->value.y += acceleration2D->value.y * deltaTime;
        acceleration2D->value.x = 0;
        acceleration2D->value.y = 0;
    }
}
zoxel_declare_system(Acceleration2DSystem)