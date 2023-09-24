ecs_entity_t font_prefab;

ecs_entity_t spawn_font_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_prefab_name("prefab_font")
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
    FontData *fontData = ecs_get_mut(world, e, FontData);
    initialize_memory_component(fontData, byte2, length)
    memcpy(fontData->value, points, length * sizeof(byte2));
    ecs_modified(world, e, FontData);
    return e;
}

// for (unsigned char i = 0; i < length; i++) fontData.value[i] = points[i]; // (byte2) { points[i].x, points[i].y };