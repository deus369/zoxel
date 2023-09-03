ecs_entity_t font_prefab;

ecs_entity_t spawn_font_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_font")
    zox_add_tag(e, Font)
    zox_add(e, FontData)
    ecs_defer_end(world);
    font_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab font [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_font(ecs_world_t *world, const byte2 points[], unsigned char length) {
    zox_instance(font_prefab)
    // zox_clone(font_prefab)
    zox_name("font")
    FontData fontData = { };
    initialize_memory_component_non_pointer(fontData, byte2, length)
    for (int i = 0; i < length; i++) fontData.value[i] = (byte2) { points[i].x, points[i].y };
    zox_set_only(e, FontData, { fontData.length, fontData.value })
    return e;
}