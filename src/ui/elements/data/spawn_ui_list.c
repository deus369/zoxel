// for only the button
typedef struct {
    ecs_entity_t prefab;
    unsigned char is_scrollbar;
} SpawnUIListData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnButtonData close_button;
    SpawnZextData zext;
    SpawnHeaderData header;
    SpawnWindowData window;
    SpawnUIListData data;
} SpawnUIList;
