void add_physics2D(ecs_world_t *world, const ecs_entity_t e, const float bounds) {
    zox_prefab_set(e, Velocity2D, {{ 0, 0 }});
    zox_prefab_set(e, Acceleration2D, {{ 0, 0 }});
    zox_prefab_set(e, Torque2D, { 0 });
    if (bounds) zox_prefab_set(e, Bounds2D, {{ bounds, bounds }});
}
