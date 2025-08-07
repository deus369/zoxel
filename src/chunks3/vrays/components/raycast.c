typedef struct {
    byte result;
    byte voxel;
    entity hit_block;
    byte3 position;
    int3 position_global;
    float3 position_real;
    float voxel_scale;
    entity chunk;
    VoxelNode *node;
    float3 hit;
    float3 normal;
    float distance;
    byte3 position_last;
    int3 position_global_last;
    float3 position_real_last;
    entity chunk_last;
    VoxelNode *node_last;
} RaycastVoxelData;
zox_custom_component(RaycastVoxelData)