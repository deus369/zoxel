typedef struct {
    VoxelNode *node;
    const entity chunk;
    const byte block_index;
    const entity block;
    const byte3 position_local;
    const int3 position_global;
    const float3 position_real;
    const float scale;
    const byte render_lod;
    const byte render_disabled;
} spawned_block_data;

zox_hook(spawned_block, (ecs* world, spawned_block_data *data), (world, data))