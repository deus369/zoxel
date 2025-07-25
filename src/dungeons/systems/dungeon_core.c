// todo: place roof
// todo: place walls
// todo: place in neighbor chunks too
// todo: every 5 seconds, build a new block along connects dungeon bricks (dark blocks)

typedef struct {
    byte3 position;
    ecs_entity_t chunk;
} TerrainPlacePosition;

void DungeonBlockSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TimerState)
    zox_sys_in(ChunkLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(ChunkLink, chunkLink)
        zox_sys_i(TimerState, timerState)
        if (timerState->value == 0) {
            continue;
        }
        const ecs_entity_t chunk = chunkLink->value;
        zox_geter_value(chunk, NodeDepth, byte, node_depth)
        zox_mut_begin(chunk, VoxelNode, node) // get node function
        // zox_geter(chunk, ChunkNeighbors, chunkNeighbors)
        int3 chunk_bounds = int3_single(powers_of_two[node_depth]);
        // const int3 size = zox_get_value(chunkLink->value, ChunkSize)
        const int3 voxel_position = zox_get_value(e, VoxelPosition)
        // get closest grass block
        // byte3 position = (byte3) { rand() % size.x, rand() % size.y, rand() % size.z };
        byte place_type = 0;
        if (rand() % 100 >= 2) {
            place_type = zox_block_dark;
        }
        // find next z position
        const byte radius = 3;
        const byte height = 5;
        int3 position = voxel_position;
        VoxelNode *update_node;
        // placing
        byte find = 0;
        for (int y = 0; y <= height && !find; y++) {
            position.y = voxel_position.y + y;
            for (int x = - radius; x <= radius && !find; x++) {
                position.x = voxel_position.x + x;
                for (int z = - radius; z <= radius && !find; z++) {
                    position.z = voxel_position.z + z;
                    if (!int3_in_bounds(position, chunk_bounds)) {
                        continue;
                    }
                    // dodge dungeon core
                    if (position.x == voxel_position.x && position.y == voxel_position.y && position.z == voxel_position.z) {
                        continue;
                    }
                    // skip middle blocks
                    if (int_abs(x) != radius && int_abs(z) != radius && (y != 0 && y != height)) {
                        continue;
                    }
                    // door
                    if (x == 0 && z == radius && y != 0 && y != height) {
                        continue;
                    }
                    update_node = get_node(node, node_depth, int3_to_byte3(position));
                    if (!update_node) {
                        continue;
                    }
                    if (update_node->value == place_type) {
                        continue;
                    }
                    // can only place in air
                    if (place_type && update_node->value) {
                        place_type = 0;
                        // continue;
                    }
                    find = 1;
                }
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
        float3 real_position = voxel_position_to_real_position(voxel_position, int3_to_byte3(chunk_bounds), default_vox_scale);
        place_block(world,
            chunkLink->value,
            update_node,
            int3_to_byte3(position),
            voxel_position,
            place_type,
            real_position);
        zox_mut_end(chunk, VoxelNode)
        // zox_log("+ Dungeon Block Placing: %s [%ix%ix%i]: %i", zox_get_name(e), position.x, position.y, position.z, place_type)
    }
} zox_declare_system(DungeonBlockSystem)