// for only the button
typedef struct {
    color color;
    ecs_entity_t prefab_zext;
    // ecs_entity_t prefab_zigel;
} SpawnButtonData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnTextData zext;
    SpawnButtonData button;
} SpawnButton;
