// our meta data on realm
ecs_entity_t spawn_realm_dungeon_core(ecs_world_t *world) {
    // dungeon block, spawns world block prefab first
    // spawn block meta
    ecs_entity_t e = spawn_realm_voxel_texture(world, zox_block_dungeon_core, "dungeon_core", "block_dungeon_core");
    // add prefab for world spawning
    const ecs_entity_t world_block = spawn_block_world_dungeon(world);
    zox_prefab_set(e, BlockPrefabLink, { world_block })
    zox_log("spawned dungeon core!")
    return e;
}