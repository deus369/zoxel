typedef struct {
    ecs_entity_t prefab;
    ecs_entity_t vox;
    unsigned char render_lod;
    unsigned char render_disabled;
    byte3 position_local;
    int3 position_global;
    float3 position_real;
} SpawnBlockVox;
