// for only the button
typedef struct {
    ecs_entity_t prefab;
    FrameTextureData texture;
} IconFrameData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    FrameTextureData texture;
    ElementSpawnData element;
    IconData icon;  // encapsulate icon data
    // SpawnTextData zext; // for now no label
} SpawnIconFrame;
