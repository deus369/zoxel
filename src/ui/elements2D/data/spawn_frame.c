// for only the button
typedef struct {
    entity prefab;
    FrameTextureData texture;
} FrameData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    FrameTextureData texture;
    ElementSpawnData element;
    IconData icon;
} SpawnFrame;