typedef struct {
    ecs_entity_t prefab;
    ecs_entity_t vox;
    byte block_index;
    byte render_lod;
    byte render_disabled;
    byte3 position_local;
    int3 position_global;
    float3 position_real;
    float scale;
} SpawnBlockVox;