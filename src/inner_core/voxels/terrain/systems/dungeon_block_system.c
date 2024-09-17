void DungeonBlockSystem(ecs_iter_t *it) {
    // todo: add generic timer for these
    // todo: every 5 seconds, build a new block along connects dungeon bricks (dark blocks)
    // zox_field_in(ChunkDirty, chunkDirtys, 1)
    for (int i = 0; i < it->count; i++) {
        // zox_field_i(ChunkDirty, chunkDirtys, chunkDirty)
        zox_log("Dungeon Block Iterating: %lu\n", it->entities[i])
    }
} zox_declare_system(DungeonBlockSystem)
