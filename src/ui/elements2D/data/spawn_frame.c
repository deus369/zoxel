// for only the button
typedef struct {
    ecs_entity_t prefab;
    FrameTextureData texture;
} FrameData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    FrameTextureData texture;
    ElementSpawnData element;
    IconData icon;
} SpawnFrame;