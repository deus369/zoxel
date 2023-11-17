ecs_entity_t font_prefab;

ecs_entity_t spawn_font_prefab(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_font")
    zox_add_tag(e, Font)
    zox_add(e, FontData)
    font_prefab = e;
#ifdef zoxel_debug_prefabs
    zox_log(" > spawn_prefab font [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_font(ecs_world_t *world, const byte2 points[], unsigned char length) {
    zox_instance(font_prefab)
    zox_name("font")
    FontData *fontData = zox_get_mut(e, FontData)
    resize_memory_component(FontData, fontData, byte2, length)
    memcpy(fontData->value, points, length * sizeof(byte2));
    zox_modified(e, FontData)
    return e;
}
