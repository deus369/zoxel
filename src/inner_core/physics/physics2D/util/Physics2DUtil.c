void AddPhysics2DComponents(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_set_component(world, e, Velocity2D, { { 0, 0 } });
    zoxel_set_component(world, e, Acceleration2D, { { 0, 0 } });
    zoxel_set_component(world, e, Torque2D, { 0 });
    zoxel_set_component(world, e, Bounds2D, { { 2.2f, 1.2f } });
}