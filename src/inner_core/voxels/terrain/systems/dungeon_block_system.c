void DungeonBlockSystem(ecs_iter_t *it) {
    // todo: add generic timer for these
    // todo: every 5 seconds, build a new block along connects dungeon bricks (dark blocks)
    zox_field_in(TimerState, timerStates, 1)
    zox_field_in(ChunkLink, chunkLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(TimerState, timerStates, timerState)
        if (timerState->value == 0) continue;
        zox_field_i(ChunkLink, chunkLinks, chunkLink)
        ChunkOctree *node = zox_get_mut(chunkLink->value, ChunkOctree) // get node function
        const int3 size = zox_get_value(chunkLink->value, ChunkSize)
        byte3 position = (byte3) { rand() % size.x, rand() % size.y, rand() % size.z };
        const int3 voxel_position = zox_get_value(it->entities[i], VoxelPosition)
        if (position.x == voxel_position.x && position.y == voxel_position.y && position.z == voxel_position.z) {
            zox_log("Dungeon Block cannot implode.\n")
            continue;
        }
        ChunkOctree *update_node = get_node(node, position);
        if (update_node == NULL) {
            zox_log("Dungeon Block Failed to Place: %lu [%ix%ix%i]\n", it->entities[i], position.x, position.y, position.z)
            continue;
        }
        // zox_log("Dungeon Block Placing: %lu [%ix%ix%i]\n", it->entities[i], position.x, position.y, position.z)
        RaycastVoxelData raycastVoxelData = {
            .chunk = chunkLink->value,
            .node = update_node,
            .position = position,
        };
        unsigned char place_type = 0;
        if (rand() % 100 >= 90) {
            place_type = zox_block_dark;
        }
        raycast_action(world, &raycastVoxelData, place_type, 2);
    }
} zox_declare_system(DungeonBlockSystem)

/*
 e cs_entity_t ch*unk;
 ChunkOctree *node;
 byte3 position;
 ecs_entity_t chunk_last;
 byte3 position_last;
 int3 normal;
 float distance;
 float3 hit;
 float3 position_real;
 unsigned char voxel;
 } RaycastVoxelData;
 */
