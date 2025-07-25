// data used when spawning any element
typedef struct {
    ecs_entity_t prefab;
    // layout2
    int2 position;
    int2 size;
    float2 anchor;
    // rendering
    byte render_disabled;
    byte layer;
    int2 texture_size;
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
