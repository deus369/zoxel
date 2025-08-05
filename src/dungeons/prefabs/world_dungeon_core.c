// prefab for our world block
ecs_entity_t spawn_block_world_dungeon(ecs_world_t *world) {
    zox_prefab();
    zox_name("block_dungeon_core");
    zox_add_tag(e, BlockDungeon);
    zox_add_tag(e, DungeonCore);
    zox_prefab_set(e, TimerRate, { dungeon_grow_rate });
    zox_prefab_set(e, TimerState, { 0 });
    zox_prefab_set(e, TimerTime, { 0 });
    zox_prefab_set(e, ChunkLink, { 0 });
    // zox_prefab_set(e, DungeonWallType, { zox_block_dark });
    zox_prefab_set(e, DungeonWallType, { zox_block_bricks });
    return e;
}