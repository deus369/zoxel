typedef struct {
    const ecs_entity_t realm;
    VoxelLinks *blocks;
} spawn_blocks_data;
// todo: move this to core voxels module
zox_hook(spawn_blocks, (ecs_world_t* world, spawn_blocks_data *data), (world, data))