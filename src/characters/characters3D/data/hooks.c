typedef struct {
    const ecs_entity_t e;
    const ecs_entity_t p;
    const char *name;
    ElementLinks *elementLinks;
} spawned_character3D_data;

zox_define_hook(spawned_character3D, (ecs_world_t* world, spawned_character3D_data data), (world, data))