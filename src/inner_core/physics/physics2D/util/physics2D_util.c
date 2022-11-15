void add_physics2D(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_set(world, e, Velocity2D, { { 0, 0 } });
    zoxel_set(world, e, Acceleration2D, { { 0, 0 } });
    zoxel_set(world, e, Torque2D, { 0 });
    zoxel_set(world, e, Bounds2D, { { 2.2f, 1.2f } });
}