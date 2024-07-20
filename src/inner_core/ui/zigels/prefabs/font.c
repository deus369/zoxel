ecs_entity_t spawn_font_prefab(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_font")
    zox_add_tag(e, Font)
    zox_add(e, FontData)
    return e;
}

ecs_entity_t spawn_font(ecs_world_t *world, const ecs_entity_t prefab, const byte2 points[], const unsigned char length) {
    zox_instance(prefab)
    zox_name("font")
    FontData *fontData = zox_get_mut(e, FontData)
    resize_memory_component(FontData, fontData, byte2, length)
    memcpy(fontData->value, points, length * sizeof(byte2));
    zox_modified(e, FontData)
    return e;
}
