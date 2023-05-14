//! Add a seed component with override.
void add_seed(ecs_world_t *world, ecs_entity_t prefab, int seed) {
    zox_set(prefab, Seed, { seed });
}

void add_dirty(ecs_world_t *world, ecs_entity_t e) {
    zox_set(e, EntityDirty, { 0 });
}