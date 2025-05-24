ecs_entity_t spawn_dungeon_core(ecs_world_t *world) {
    // dungeon block, spawns world block prefab first
    // todo: move t this into a seperate prefab - dungeon_block_world
    zox_neww(dungeon_block_world)
    zox_make_prefab(dungeon_block_world)
    zox_add_tag(dungeon_block_world, BlockDungeon)
    zox_prefab_set(dungeon_block_world, TimerRate, { 5 })
    zox_prefab_set(dungeon_block_world, TimerState, { 0 })
    zox_prefab_set(dungeon_block_world, TimerTime, { 0 })
    zox_prefab_set(dungeon_block_world, ChunkLink, { 0 })
    // spawn block meta
    ecs_entity_t e = spawn_realm_voxel_texture(world, zox_block_dungeon_core, "dungeon_core", "block_dungeon_core");
    // add prefab for world spawning
    zox_prefab_set(e, BlockPrefabLink, { dungeon_block_world })
    return e;
}