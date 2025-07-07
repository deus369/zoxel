ecs_entity_t spawn_font_prefab(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_font")
    zox_add_tag(e, Font)
    zox_prefab_add(e, FontData)
    return e;
}

ecs_entity_t spawn_font(ecs_world_t *world, const ecs_entity_t prefab, const byte2 *points, const byte length) {
    if (!points || length == 0) {
        zox_log("! [spawn_font] cannot spawn null points\n")
        return 0;
    }
    zox_instance(prefab)
    zox_name("font")
    FontData *data = &((FontData) { 0, NULL });
    // zox_get_muter(e, FontData, fontData)
    resize_memory_component(FontData, data, byte2, length)
    memcpy(data->value, points, length * sizeof(byte2));
    zox_set(e, FontData, { data->length, data->value })
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