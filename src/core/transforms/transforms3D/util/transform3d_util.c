//! Add transform2D components onto an entity.
void add_transform3Ds(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_set(world, e, Position3D, { { 0, 0, 0 } });
    zoxel_set(world, e, Rotation3D, { float4_identity() });
    zoxel_set(world, e, Scale1D, { 1 });
}