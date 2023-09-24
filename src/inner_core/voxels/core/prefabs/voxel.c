ecs_entity_t prefab_voxel;

ecs_entity_t spawn_prefab_voxel(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_add_tag(e, Voxel)
    zox_set(e, TextureLinks, { 0, NULL })
    ecs_defer_end(world);
    prefab_voxel = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawned prefab voxel [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_voxel(ecs_world_t *world, unsigned char index) {
    zox_instance(prefab_voxel)
    // spawn one texture here
    TextureLinks *textureLinks = ecs_get_mut(world, e, TextureLinks);
    initialize_memory_component(textureLinks, ecs_entity_t, 1)
    for (int i = 0; i < 1; i++) {
        ecs_entity_t texture_entity = spawn_texture_dirt(world);
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
        textureLinks->value[i] = texture_entity;
    }
    ecs_modified(world, e, TextureLinks);
    #ifdef zoxel_debug_spawns
        zoxel_log(" + spawned voxel [%lu]\n", (long int) e);
    #endif
    return e;
}