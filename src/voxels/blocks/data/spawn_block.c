typedef struct {
    ecs_entity_t prefab;
    ecs_entity_t prefab_block_vox;
    char *name;
    unsigned char index;
    unsigned char model;
    unsigned char textures;
    char *texture_filename;
    unsigned char disable_collision; // enabled by default
    color color;
    ecs_entity_t tag;
    ecs_entity_t texture_tag;
    // generation
    int seed;
    // textures
    ecs_entity_t prefab_texture;
    // vox
    ecs_entity_t vox;
    unsigned char bake_vox;
    unsigned char vox_offset;
} SpawnBlock;
