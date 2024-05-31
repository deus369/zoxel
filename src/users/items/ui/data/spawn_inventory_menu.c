// all t the spawn data used for spawn
typedef struct {
    byte2 grid_size;
    unsigned char icon_size;
    unsigned char grid_padding;
    unsigned char grid_margins;
    ecs_entity_t character;
} InventoryMenuData;

typedef struct {
    ecs_entity_t prefab;
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnZextData header_zext;
    SpawnHeaderData header;
    SpawnButtonData close_button;
    InventoryMenuData inventory_menu;
    IconFrameData icon_frame;
    IconData icon;
} SpawnInventoryMenu;
