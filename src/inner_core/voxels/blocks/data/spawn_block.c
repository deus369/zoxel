typedef struct {
    ecs_entity_t prefab;
    unsigned char index;
    unsigned char model;
    int seed;
    color color;
    ecs_entity_t tag;
    ecs_entity_t texture_tag;
} SpawnBlock;
