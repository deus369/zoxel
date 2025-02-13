typedef struct {
    ecs_entity_t prefab;
    ecs_entity_t prefab_block_vox;
    char *name;
    byte index;
    byte model;
    byte textures;
    char *texture_filename;
    byte disable_collision; // enabled by default
    color color;
    ecs_entity_t tag;
    ecs_entity_t texture_tag;
    // generation
    int seed;
    // textures
    ecs_entity_t prefab_texture;
    // vox
    ecs_entity_t vox;
    byte bake_vox;
    byte vox_offset;
} SpawnBlock;
