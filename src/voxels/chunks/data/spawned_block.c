typedef struct {
    const byte block_index;
    const ecs_entity_t block;
    const byte3 position_local;
    const int3 position_global;
    const float3 position_real;
    const float scale;
    const ecs_entity_t chunk;
    VoxelNode *node;
} spawned_block_data;

zox_hook(spawned_block, (ecs_world_t* world, spawned_block_data *data), (world, data))