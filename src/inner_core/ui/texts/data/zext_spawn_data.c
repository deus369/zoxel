// when spawning Zext
typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    ecs_entity_t prefab;
    const char* text;
    int font_size;
    byte2 padding;
    color font_fill_color;
    color font_outline_color;
    unsigned char alignment;
} ZextSpawnData;
