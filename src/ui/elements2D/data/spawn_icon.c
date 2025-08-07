// for only the button
typedef struct {
    entity prefab;
    FrameTextureData texture;
    int size;
    int index;
    int2 texture_size;
} IconData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    FrameTextureData texture;
    ElementSpawnData element;
    int index;
    int2 texture_size;
} SpawnIcon;