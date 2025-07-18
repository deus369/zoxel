typedef struct {
    byte voxel;
    ecs_entity_t hit_block;
    byte3 position;
    int3 position_global;
    float3 position_real;
    float voxel_scale;
    ecs_entity_t chunk;
    VoxelNode *node;
    float3 hit;
    int3 normal;
    float distance;
    byte3 position_last;
    int3 position_global_last;
    float3 position_real_last;
    ecs_entity_t chunk_last;
    VoxelNode *node_last;
} RaycastVoxelData;
zox_custom_component(RaycastVoxelData)