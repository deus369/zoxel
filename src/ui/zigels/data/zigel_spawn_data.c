// used for spawning zigels
typedef struct {
    byte zigel_index; // zox character code
    int data_index;   // a link to TextData index
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
