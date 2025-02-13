// data used when spawning any element
typedef struct {
    ecs_entity_t prefab;
    int2 position;
    int2 size;
    float2 anchor;
    byte layer;
    byte render_disabled;
    // outputs
    int2 position_in_canvas;
} ElementSpawnData;

typedef struct {
    color fill_color;
    color outline_color;
} FrameTextureData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    FrameTextureData texture;
    ElementSpawnData element;
} ElementSpawn;
