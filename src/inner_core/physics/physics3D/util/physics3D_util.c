void add_physics3D(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_set(world, e, Velocity3D, { { 0, 0 } });
    zoxel_set(world, e, Acceleration3D, { { 0, 0 } });
    zoxel_set(world, e, Torque3D, { { 0, 0, 0, 0 } });
    zoxel_set(world, e, Bounds3D, { { 2.2f, 1.2f, 2.2f } });
}