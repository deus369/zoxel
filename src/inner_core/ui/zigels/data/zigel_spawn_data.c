// used for spawning zigels
typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ZigelZextSpawnData zext;
    ElementSpawnData element;
    unsigned char zigel_index;
    unsigned char data_index;   // a link to ZextData index
    color fill_color; // fill
    color outline_color;
} ZigelSpawnData;
