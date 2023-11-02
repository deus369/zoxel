ecs_entity_t prefab_texture_dirt;

ecs_entity_t spawn_prefab_texture_dirt(ecs_world_t *world) {
    // int2 texture_size = (int2) { 16, 16 };
    int2 texture_size = (int2) { 32, 32 };
    zox_prefab()
    zox_prefab_name("prefab_texture_dirt")
    // zox_add_tag(e, DirtTexture)
    add_seed(world, e, 666);
    add_texture(world, e, texture_size, 1);
    add_noise_texture(world, e);
    // add_dirty(world, e);
    prefab_texture_dirt = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab texture_dirt [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_texture_dirt(ecs_world_t *world, int seed) {
    zox_instance(prefab_texture_dirt)
    zox_name("texture")
    zox_set(e, Seed, { seed })
    #ifdef zoxel_debug_spawns
        zox_log("   + spawned texture_dirt [%lu]\n", e)
    #endif
    return e;
}
