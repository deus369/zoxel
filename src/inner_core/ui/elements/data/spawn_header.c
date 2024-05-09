// for only the button
typedef struct {
    ecs_entity_t prefab;
    color color;
} SpawnHeaderData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnButtonData close_button;
    SpawnZextData zext;
    SpawnHeaderData header;
} SpawnHeader;
