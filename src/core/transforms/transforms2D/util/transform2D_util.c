//! Add transform2D components onto an entity.
void add_transform2Ds(ecs_world_t *world, ecs_entity_t e) {
    zoxel_set(world, e, Position2D, { { 0, 0 } });
    zoxel_set(world, e, Rotation2D, { 0 });
    zoxel_set(world, e, Scale1D, { 1 });
}

void add_transform2Ds_scale2D(ecs_world_t *world, ecs_entity_t e) {
    zoxel_set(world, e, Position2D, { { 0, 0 } });
    zoxel_set(world, e, Rotation2D, { 0 });
    zoxel_set(world, e, Scale2D, { { 1, 1 } });
}