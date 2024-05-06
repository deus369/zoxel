// used for spawning zigels
typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ZigelZextSpawnData zext;
    unsigned char zigel_index;
    unsigned char array_index;
    int2 position;
    int2 size;
    float2 anchor;
    unsigned char layer;
    color fill_color; // fill
    color outline_color;
} ZigelSpawnData;
