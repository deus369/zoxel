ecs_entity_t spawn_prefab_statbar2D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_statbar2D")
    zox_add_tag(e, Statbar)
    zox_prefab_set(e, StatLink, { 0 })
    return e;
}

ecs_entity_t spawn_statbar2D(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent, const ecs_entity_t player, const ecs_entity_2 character_group) {
    const byte layer = 1;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const float2 elementbar2D_anchor = float2_top_left;
    const int2 size = (int2) { 256, 32 };
    const byte2 padding = (byte2) { 16, 8 };
    const int2 healthbar_position = (int2) { 8, 8 - size.y / 2 };
    const ecs_entity_t healthbar_2D = spawn_elementbar2D(world, prefab_statbar2D, player, canvas, parent, healthbar_position, size, padding, elementbar2D_anchor, layer, int2_half(canvas_size), canvas_size, canvas_size, 0);
    // const ecs_entity_t character = zox_get_value(player, CharacterLink)
    if (character_group.x) {
        // const StatLinks *statLinks = zox_get(character, StatLinks)
        zox_set(healthbar_2D, StatLink, { character_group.y })
    }
    return healthbar_2D;
}
