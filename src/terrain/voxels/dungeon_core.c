ecs_entity_t spawn_block_world_dungeon(ecs_world_t *world) {
    const float dungeon_grow_rate = 0.5f; // dungeon_grow_rate
    zox_neww(e)
    zox_make_prefab(e);
    zox_name("block_dungeon_core")
    zox_add_tag(e, BlockDungeon)
    zox_prefab_set(e, TimerRate, { dungeon_grow_rate })
    zox_prefab_set(e, TimerState, { 0 })
    zox_prefab_set(e, TimerTime, { 0 })
    zox_prefab_set(e, ChunkLink, { 0 })
    return e;
}

ecs_entity_t spawn_block_dungeon_core(ecs_world_t *world) {
    const ecs_entity_t e2 = spawn_block_world_dungeon(world);
    // dungeon block, spawns world block prefab first
    // spawn block meta
    ecs_entity_t e = spawn_realm_voxel_texture(world, zox_block_dungeon_core, "dungeon_core", "block_dungeon_core");
    // add prefab for world spawning
    zox_prefab_set(e, BlockPrefabLink, { e2 })
    return e;
}