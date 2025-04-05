// when spawning Zext
typedef struct {
    const char* text;
    byte font_size;              // zigel_size
    byte font_thickness;              // zigel_size
    byte alignment;    // mesh_alignment
    byte2 padding;              // around zigels
    color font_fill_color;
    color font_outline_color;
} SpawnTextData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnTextData zext;
} SpawnZext;
