// for only the button
typedef struct {
    ecs_entity_t prefab;
    FrameTextureData texture;
    int size;
    int index;
} IconData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    FrameTextureData texture;
    ElementSpawnData element;
    int index;
} SpawnIcon;
