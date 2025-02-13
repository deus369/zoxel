// all t the spawn data used for spawn
typedef struct {
    ecs_entity_t prefab_header;
    ecs_entity_t prefab_header_text;
    byte2 grid_size;
    byte icon_size;
    byte grid_padding;
    byte grid_margins;
    ecs_entity_t character;
    ecs_entity_t user_links_id;
} SpawnWindowUsersData;

typedef struct {
    CanvasSpawnData canvas;
    ParentSpawnData parent;
    ElementSpawnData element;
    SpawnZextData header_zext;
    SpawnHeaderData header;
    SpawnButtonData close_button;
    IconFrameData icon_frame;
    IconData icon;
    SpawnWindowUsersData window;
} SpawnWindowUsers;
