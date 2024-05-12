// for only the button
typedef struct {
    color fill_color;
    color outline_color;
} IconData;

typedef struct {
    ecs_entity_t prefab;
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    IconData icon;
} SpawnIcon;
