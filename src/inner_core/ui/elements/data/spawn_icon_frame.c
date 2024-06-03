// for only the button
typedef struct {
    ecs_entity_t prefab;
    color fill_color;
    color outline_color;
} IconFrameData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    // SpawnZextData zext; // for now no label
    IconData icon;
    IconFrameData icon_frame;
} SpawnIconFrame;
