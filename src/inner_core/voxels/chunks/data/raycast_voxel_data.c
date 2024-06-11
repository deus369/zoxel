// todo: attach this data as component to player
typedef struct {
    ecs_entity_t chunk;
    byte3 position;
    ecs_entity_t chunk_last;
    byte3 position_last;
    float3 hit;
    int3 normal;
} RaycastVoxelData;
zox_custom_component(RaycastVoxelData)
