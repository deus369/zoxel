//! Add transform2D components onto an entity.
void add_transform3Ds(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_set_component(world, e, Position, { { 0, 0, 0 } });
    zoxel_set_component(world, e, Rotation, { { 0, 0, 0, 1 } });
    zoxel_set_component(world, e, Scale1D, { 1 });
}