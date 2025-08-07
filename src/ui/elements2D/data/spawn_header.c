// for only the button
typedef struct {
    entity prefab_zext;
    byte is_close_button;
    byte margins;
    color color;
} SpawnHeaderData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnButtonData close_button;
    SpawnTextData zext;
    SpawnHeaderData header;
} SpawnHeader;
