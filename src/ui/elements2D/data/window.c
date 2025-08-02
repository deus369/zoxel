// for only the button
typedef struct {
    ecs_entity_t prefab;
    color fill;
    color outline;
} SpawnWindowData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnButtonData close_button;
    SpawnTextData zext;
    SpawnHeaderData header;
    SpawnWindowData window;
} SpawnWindow;


typedef struct {
    // header
    const char *header_text;
    const byte header_font_size;
    const byte2 header_padding;
    // list area
    byte is_scrollbar;

    // todo
    color fill;
    color outline;

    // output
    Children* children;
} SpawnWindow2;