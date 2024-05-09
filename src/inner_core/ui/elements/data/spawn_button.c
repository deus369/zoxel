// for only the button
typedef struct {
    ecs_entity_t prefab;
    color color;
} SpawnButtonData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnZextData zext;
    SpawnButtonData button;
} SpawnButton;
