ecs_entity_t prefab_voxel;

ecs_entity_t spawn_prefab_voxel(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_add_tag(e, Voxel)
    zox_set(e, TextureLinks, { 0, NULL })
    ecs_defer_end(world);
    prefab_voxel = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab voxel [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_voxel(ecs_world_t *world, unsigned char index) {
    ecs_defer_begin(world);
    zox_instance(prefab_voxel)
    // spawn one texture here
    TextureLinks textureLinks = { };
    initialize_memory_component_non_pointer(textureLinks, ecs_entity_t, 1)
    for (int i = 0; i < 1; i++) {
        ecs_entity_t texture_entity = spawn_texture_dirt(world);
        if (index == 1) {
            zox_add_tag(texture_entity, GrassTexture)
        } else if (index == 2) {
            zox_add_tag(texture_entity, SandTexture)
        }
        textureLinks.value[i] = texture_entity;
    }
    zox_set_only(e, TextureLinks, { textureLinks.length, textureLinks.value })
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log(" + spawned voxel [%lu]\n", (long int) e);
    #endif
    return e;
}