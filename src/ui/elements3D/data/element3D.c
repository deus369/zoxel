typedef struct {
    ecs_entity_t prefab;
    byte render_disabled;
    int2 position;
    int2 size;
    // float2 anchor;
    // byte layer;
} Element3DData;

typedef struct {
    float trail_offset;
    ecs_entity_t ui_holder;
    ecs_entity_t prefab;
    byte render_disabled;
    color base_color;
} SpawnDataElement3D;

