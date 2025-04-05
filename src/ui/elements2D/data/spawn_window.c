// for only the button
typedef struct {
    ecs_entity_t prefab;
    color color;
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
