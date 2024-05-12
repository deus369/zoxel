// for only the button
typedef struct {
    ecs_entity_t prefab;
    unsigned char is_close_button;
    unsigned char margins;
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
