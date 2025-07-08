// todo: place roof
// todo: place walls
// todo: place in neighbor chunks too

typedef struct {
    byte3 position;
    ecs_entity_t chunk;
} TerrainPlacePosition;

void DungeonBlockSystem(ecs_iter_t *it) {
    // todo: every 5 seconds, build a new block along connects dungeon bricks (dark blocks)
    zox_field_world()
    zox_field_in(TimerState, timerStates, 1)
    zox_field_in(ChunkLink, chunkLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(TimerState, timerStates, timerState)
        if (timerState->value == 0) {
            continue;
        }
        zox_field_e()
        zox_field_i(ChunkLink, chunkLinks, chunkLink)
        const ecs_entity_t chunk = chunkLink->value;
        zox_mut_begin(chunk, ChunkOctree, node) // get node function
        int3 chunk_bounds = int3_single(powers_of_two[node->linked]);
        // const int3 size = zox_get_value(chunkLink->value, ChunkSize)
        const int3 voxel_position = zox_get_value(e, VoxelPosition)
        // get closest grass block
        //byte3 position = (byte3) { rand() % size.x, rand() % size.y, rand() % size.z };
        byte place_type = 0;
        if (rand() % 100 >= 2) {
            place_type = zox_block_dark;
        }
        // find next z position
        const byte range = 8;
        byte find = 0;
        int3 position = voxel_position; // int3_to_byte3(voxel_position);
        ChunkOctree *update_node;
        // placing
        for (int j = - range; j <= range; j++) {
            position.x = voxel_position.x + j;
            for (int k = - range; k <= range; k++) {
                position.z = voxel_position.z + k;
                // dodge dungeon core
                if (position.x == voxel_position.x && position.y == voxel_position.y && position.z == voxel_position.z) {
                    continue;
                }
                if (!int3_in_bounds(position, chunk_bounds)) {
                    continue;
                }
                update_node = get_node(node, int3_to_byte3(position));
                if (!update_node) {
                    continue;
                }
                if (update_node->value == place_type) {
                    continue;
                }
                find = 1;
                break;
            }
            if (find) {
                break;
            }
        }
        if (!find) {
            continue;
        }
        /*if (position.x == voxel_position.x && position.y == voxel_position.y && position.z == voxel_position.z) {
            zox_log("Dungeon Block cannot implode.\n")
            continue;
        }*/
        //
        //RaycastVoxelData raycastVoxelData = {
        //    .chunk = chunkLink->value,
        //    .node = update_node,
        //    .position = position,
        //};
        zox_log("+ Dungeon Block Placing: %s [%ix%ix%i]: %i", zox_get_name(e), position.x, position.y, position.z, place_type)
        float3 real_position = voxel_position_to_real_position(voxel_position, byte3_single(powers_of_two[node->linked]), default_vox_scale);
        voxel_action(world, chunkLink->value, update_node, int3_to_byte3(position), place_type, real_position);
        zox_mut_end(chunk, ChunkOctree)
        //raycast_action(world, &raycastVoxelData, place_type, 2);
    }
} zox_declare_system(DungeonBlockSystem)