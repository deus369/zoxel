typedef struct {
    const ecs_entity_t realm;
    const ecs_entity_t e;
    const ecs_entity_t p;
    const char *name;
    const byte render_disabled;
    ecs_entity_t health;
    const ecs_entity_t *stats;
    byte stats_length;
    ElementLinks *elementLinks;
} spawned_character3D_data;

zox_hook(spawned_character3D, (ecs_world_t* world, spawned_character3D_data *data), (world, data))