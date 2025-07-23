typedef struct {
    const ecs_entity_t realm;
    const ecs_entity_t e;
    const ecs_entity_t p;
    // spawn info
    const char *name;
    const byte render_disabled;
    ecs_entity_t health;
    float soul_value;
    // massive links
    ElementLinks *elementLinks;
    const ecs_entity_t *stats;
    byte stats_length;
} spawned_character3D_data;

zox_hook(spawned_character3D, (ecs_world_t* world, spawned_character3D_data *data), (world, data))