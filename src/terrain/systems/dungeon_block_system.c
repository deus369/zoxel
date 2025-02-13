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
        // const int3 size = zox_get_value(chunkLink->value, ChunkSize)
        const int3 voxel_position = zox_get_value(it->entities[i], VoxelPosition)
        // get closest grass block
        //byte3 position = (byte3) { rand() % size.x, rand() % size.y, rand() % size.z };
        byte place_type = 0;
        if (rand() % 100 >= 2) {
            place_type = zox_block_dark;
        }
        // find next z position
        const byte range = 5;
        byte find = 0;
        byte3 position = int3_to_byte3(voxel_position);
        ChunkOctree *update_node;
        if (place_type == 0) {
            position.z += range;
            position.x += range;
            for (int j = 0; j < range; j++) {
                position.x = voxel_position.x + range - j;
                for (int k = 0; k < range; k++, position.z--) {
                    position.z = voxel_position.z + range - k;
                    if (position.x == voxel_position.x && position.y == voxel_position.y && position.z == voxel_position.z) continue;
                    update_node = get_node(node, position);
                    if (update_node == NULL) continue;
                    if (update_node->value == 0) continue;
                    find = 1;
                    break;
                }
                if (find) break;
            }
        } else {
            // placing
            for (int j = 0; j < range; j++) {
                position.x = voxel_position.x + j;
                for (int k = 0; k < range; k++) {
                    position.z = voxel_position.z + k;
                    if (position.x == voxel_position.x && position.y == voxel_position.y && position.z == voxel_position.z) continue;
                    update_node = get_node(node, position);
                    if (update_node == NULL) continue;
                    if (update_node->value != 0) continue;
                    find = 1;
                    break;
                }
                if (find) break;
            }
        }
        if (!find) continue;
        /*if (position.x == voxel_position.x && position.y == voxel_position.y && position.z == voxel_position.z) {
            zox_log("Dungeon Block cannot implode.\n")
            continue;
        }*/
        // zox_log("Dungeon Block Placing: %lu [%ix%ix%i]\n", it->entities[i], position.x, position.y, position.z)
        //RaycastVoxelData raycastVoxelData = {
        //    .chunk = chunkLink->value,
        //    .node = update_node,
        //    .position = position,
        //};
        voxel_action(world, chunkLink->value, update_node->nodes, position, place_type, update_node);
        //raycast_action(world, &raycastVoxelData, place_type, 2);
    }
} zox_declare_system(DungeonBlockSystem)
