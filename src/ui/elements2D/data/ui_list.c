// for only the button
typedef struct {
    SpawnListElement* elements;
    int count;
    int visible_count;
    byte font_size;
    color fill;
    color outline;
    // from window
    Children *children;
} SpawnList;

/*typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnButtonData close_button;
    SpawnTextData zext;
    SpawnHeaderData header;
    SpawnWindowData window;
    SpawnUIListData data;
} SpawnUIList;
*/