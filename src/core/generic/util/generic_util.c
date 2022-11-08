//! Add a seed component with override.
void add_seed(ecs_world_t *world, ecs_entity_t prefab, int seed)
{
    zoxel_set_component(world, prefab, Seed, { seed });
}

void add_dirty(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_set_component(world, e, EntityDirty, { 0 });
}