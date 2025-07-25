typedef struct {
    ecs_entity_t prefab;
    const ecs_entity_t player;
    const float3 position;
    const float4 rotation;
    const float3 euler;
    const ecs_entity_t terrain;
    const ecs_entity_t terrain_chunk;
    const int3 chunk_position;
    const byte lod;
    float scale;
    const byte render_disabled;
    const ecs_entity_t model;
    // const ecs_entity_t vox;
} spawn_character3D_data;