// for only the button
typedef struct {
    ecs_entity_t prefab_zext;
    color fill;
    color outline;
} SpawnButtonData;

// just use for holding atm
typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnTextData zext;
    SpawnButtonData button;
} SpawnButton;