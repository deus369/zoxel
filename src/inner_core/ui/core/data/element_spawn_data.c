// data used when spawning any element
typedef struct {
    int2 position;
    int2 size;
    float2 anchor;
    unsigned char layer;
    unsigned char render_disabled;
    color fill_color;
    int2 position_in_canvas;
} ElementSpawnData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    ecs_entity_t prefab;
} SpawnElement;
