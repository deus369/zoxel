ecs_entity_t prefab_voxel;

ecs_entity_t spawn_prefab_voxel(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_voxel")
    zox_add_tag(e, Voxel)
    zox_prefab_set(e, Textures, { 0, NULL })
    prefab_voxel = e;
    #ifdef zoxel_debug_prefabs
        zox_log(" + spawned prefab voxel [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_voxel(ecs_world_t *world, unsigned char index) {
    zox_instance(prefab_voxel)
    zox_name("voxel")
    // spawn one texture here
    int seed = (rand() % 666666) - 333333 + index;
    Textures *textures = zox_get_mut(e, Textures)
    resize_memory_component(Textures, textures, ecs_entity_t, 1)
    for (int i = 0; i < 1; i++) {
        ecs_entity_t texture_entity = spawn_texture_dirt(world, seed + i);
        // todo: just set a flag for TextureGenerationType
        if (index == 0) {
            zox_add_tag(texture_entity, DirtTexture)
        } else if (index == 1) {
            zox_add_tag(texture_entity, GrassTexture)
        } else if (index == 2) {
            zox_add_tag(texture_entity, SandTexture)
        } else if (index == 3) {
            zox_add_tag(texture_entity, StoneTexture)
        } else if (index == 4) {
            zox_add_tag(texture_entity, ObsidianTexture)
        }
        textures->value[i] = texture_entity;
    }
    zox_modified(e, Textures)
    #ifdef zoxel_debug_spawns
        zox_log(" + spawned voxel [%lu]\n", e)
    #endif
    return e;
}
