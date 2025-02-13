ecs_entity_t spawn_font_prefab(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_font")
    zox_add_tag(e, Font)
    zox_add(e, FontData)
    return e;
}

ecs_entity_t spawn_font(ecs_world_t *world, const ecs_entity_t prefab, const byte2 points[], const byte length) {
    zox_instance(prefab)
    zox_name("font")
    zox_get_muter(e, FontData, fontData)
    resize_memory_component(FontData, fontData, byte2, length)
    memcpy(fontData->value, points, length * sizeof(byte2));
    return e;
}

// doesn't clone points
ecs_entity_t spawn_font_direct(ecs_world_t *world, const ecs_entity_t prefab, byte2 *points, const byte length) {
    zox_instance(prefab)
    zox_name("font")
    zox_get_muter(e, FontData, fontData)
    fontData->length = length;
    fontData->value = points;
    return e;
}

