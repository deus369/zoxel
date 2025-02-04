// used for spawning zigels
typedef struct {
    unsigned char zigel_index; // zox character code
    int data_index;   // a link to ZextData index
    color fill_color; // fill
    color outline_color;
} SpawnZigelData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    ZigelZextSpawnData zext;    // just copy zext data in?
    SpawnZigelData zigel;
} SpawnZigel;
