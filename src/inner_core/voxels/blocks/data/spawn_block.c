typedef struct {
    ecs_entity_t prefab;
    unsigned char index;
    unsigned char model;
    ecs_entity_t vox;
    ecs_entity_t vox_texture;
    unsigned char textures;
    int seed;
    color color;
    ecs_entity_t tag;
    ecs_entity_t texture_tag;
    unsigned char disable_collision; // enabled by default
} SpawnBlock;
