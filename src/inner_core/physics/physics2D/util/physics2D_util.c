void add_physics2D(ecs_world_t *world, ecs_entity_t e) {
    zox_prefab_set(e, Velocity2D, { { 0, 0 } });
    zox_prefab_set(e, Acceleration2D, { { 0, 0 } });
    zox_prefab_set(e, Torque2D, { 0 });
    zox_prefab_set(e, Bounds2D, { { 2.2f, 1.2f } });
}