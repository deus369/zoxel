// for only the button
typedef struct {
    color fill_color;
    color outline_color;
} IconFrameData;

typedef struct {
    ecs_entity_t prefab;
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    // SpawnZextData zext; // for now no label
    IconFrameData icon_frame;
    IconData icon;
} SpawnIconFrame;
