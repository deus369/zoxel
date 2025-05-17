typedef struct {
    ecs_entity_t prefab;
    const ecs_entity_t vox;
    const ecs_entity_t player;
    const float3 position;
    const float4 rotation;
    const ecs_entity_t terrain;
    const ecs_entity_t terrain_chunk;
    const byte lod;
    float scale;
    const byte render_disabled;
} spawn_character3D_data;