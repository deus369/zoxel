void add_physics2D(ecs_world_t *world, ecs_entity_t e) {
    zox_set(e, Velocity2D, { { 0, 0 } });
    zox_set(e, Acceleration2D, { { 0, 0 } });
    zox_set(e, Torque2D, { 0 });
    zox_set(e, Bounds2D, { { 2.2f, 1.2f } });
}