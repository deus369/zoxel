// when spawning Zext
typedef struct {
    // ecs_entity_t prefab;
    const char* text;
    byte font_size;              // zigel_size
    byte font_thickness;              // zigel_size
    byte alignment;    // mesh_alignment
    byte2 padding;              // around zigels
    color font_fill_color;
    color font_outline_color;
} SpawnZextData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnZextData zext;
} SpawnZext;
