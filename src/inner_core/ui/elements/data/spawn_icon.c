// for only the button
typedef struct {
    ecs_entity_t prefab;
    FrameTextureData texture;
} IconData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    FrameTextureData texture;
    ElementSpawnData element;
} SpawnIcon;
