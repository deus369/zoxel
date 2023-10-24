ecs_entity_t prefab_zigel;

ecs_entity_t spawn_zigel_prefab(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_zigel")
    zox_add_tag(e, Zigel)
    zox_add_tag(e, FontTexture)
    zox_prefab_set(e, ZigelIndex, { 0 })
    zox_prefab_set(e, Color, {{ 55, 185, 125, 255 }})
    add_ui_plus_components(world, e);
    prefab_zigel = e;
    #ifdef zoxel_debug_prefabs
        zox_log(" > spawn_prefab zigel [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_zigel(ecs_world_t *world, ecs_entity_t zext, unsigned char index, int2 position, int2 size, float2 anchor, unsigned char layer, float2 parent_position2D, int2 parent_pixel_size, int2 canvas_size) {
    color zigel_color = (color) { 55 + rand() % 60, 150 + rand() % 75, 135 + rand() % 70, 255 };
    zox_instance(prefab_zigel)
    zox_name("zigel")
    zox_set(e, ZigelIndex, { index })
    zox_set(e, Color, { zigel_color })
    initialize_ui_components_2(world, e, zext, position, size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    #ifdef zoxel_debug_spawns
        zox_log("   > spawned zigel [%lu]\n", e)
    #endif
    return e;
}
