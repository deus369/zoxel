typedef struct {
    const ecs_entity_t chunk;
    const ecs_entity_t *blocks;
    const ecs_entity_t *models;
    const ecs_entity_t *block_prefabs;
    const byte *block_vox_offsets;
    const byte models_count;
    const float3 chunk_position_real;
    const float scale;
    SpawnBlockVox *spawn_data;
} UpdateBlockEntities;