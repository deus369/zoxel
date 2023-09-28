void add_seed(ecs_world_t *world, ecs_entity_t prefab, int seed) {
    zox_set(prefab, Seed, { seed });
}