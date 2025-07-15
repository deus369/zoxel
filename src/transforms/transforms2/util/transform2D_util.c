//! Add transform2D components onto an entity.
/*void add_transform2Ds(ecs_world_t *world, ecs_entity_t e) {
    zox_prefab_set(e, Position2D, { float2_zero })
    zox_prefab_set(e, Rotation2D, { 0 })
    zox_prefab_set(e, Scale1D, { 1 })
}*/

void add_transform2Ds_scale2D(ecs_world_t *world, ecs_entity_t e) {
    zox_prefab_set(e, Position2D, { { 0, 0 } });
    zox_prefab_set(e, Rotation2D, { 0 });
    zox_prefab_set(e, Scale2D, { { 1, 1 } });
}