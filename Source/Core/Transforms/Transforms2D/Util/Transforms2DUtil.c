//! Add transform2D components onto an entity.
void AddTransforms2DComponents(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_set_component(world, e, Position2D, { { 0, 0 } });
    zoxel_set_component(world, e, Rotation2D, { 0 });
    zoxel_set_component(world, e, Scale1D, { 1 });
}