// todo: attach this data as component to player
typedef struct {
    ecs_entity_t chunk;
    ChunkOctree *node;
    byte3 position;
    ecs_entity_t chunk_last;
    byte3 position_last;
    int3 normal;
    float distance;
    float3 hit;
    float3 position_real;
    byte voxel;
    ecs_entity_t voxel_entity;
    float voxel_scale;
} RaycastVoxelData;
zox_custom_component(RaycastVoxelData)
