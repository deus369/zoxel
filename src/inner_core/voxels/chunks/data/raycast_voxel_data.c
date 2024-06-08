// todo: attach this data as component to player
typedef struct {
    ecs_entity_t chunk;
    byte3 position;
    int3 normal;
    ecs_entity_t chunk_last;
    byte3 position_last;
} RaycastVoxelData;
zox_custom_component(RaycastVoxelData)
