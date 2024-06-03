// for only the button
typedef struct {
    ecs_entity_t prefab;
    color fill_color;
    color outline_color;
} IconData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    IconData icon;
} SpawnIcon;
