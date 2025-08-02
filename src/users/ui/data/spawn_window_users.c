// all t the spawn data used for spawn
typedef struct {
    ecs_entity_t prefab_header;
    ecs_entity_t prefab_header_text;
    byte2 grid_size;
    byte icon_size;
    byte2 grid_padding;
    byte2 grid_margins;
    ecs_entity_t character;
    ecs_entity_t user_links_id;
} SpawnWindowUsersData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnTextData header_zext;
    SpawnHeaderData header;
    SpawnButtonData close_button;
    FrameData frame;
    IconData icon;
    SpawnWindowUsersData window;
} SpawnWindowUsers;
