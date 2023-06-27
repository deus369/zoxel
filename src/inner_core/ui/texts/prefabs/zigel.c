ecs_entity_t zigel_prefab;

ecs_entity_t spawn_zigel_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_zigel")
    zox_add_tag(e, Zigel)
    zox_set(e, ZigelIndex, { 0 })
    zox_add_tag(e, FontTexture)
    zox_set(e, Color, {{ 55, 185, 125, 255 }})
    add_ui_plus_components(world, e);
    ecs_defer_end(world);
    zigel_prefab = e;
    #ifdef zoxel_debug_prefabs
        printf("spawn_prefab zigel [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_zigel(ecs_world_t *world, ecs_entity_t zext, unsigned char index, int2 position, int2 size,
    float2 anchor, unsigned char layer, float2 parent_position2D, int2 parent_pixel_size, int2 canvas_size) {
    // ecs_defer_begin(world);
    zox_instance(zigel_prefab)
    zox_name("zigel")
    zox_set(e, ZigelIndex, { index })
    zox_set(e, Color, {{ 55 + rand() % 60, 150 + rand() % 75, 135 + rand() % 70, 255 }})
    initialize_ui_components_2(world, e, zext, position, size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    // ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned zigel [%lu]\n", (long int) e);
    #endif
    return e;
}