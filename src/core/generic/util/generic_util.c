void add_seed(ecs_world_t *world, ecs_entity_t prefab, int seed) {
    zox_prefab_set(prefab, Seed, { seed });
}