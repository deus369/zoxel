ecs_entity_t spawn_prefab_icon_overlay(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("icon_overlay")
    zox_prefab_set(e, ParentLink, { 0 })
    zox_set(e, Color, { icon_overlay_fill_color })
    zox_set(e, OutlineColor, { icon_overlay_outline_color })
    zox_set(e, RenderDisabled, { 1 })
    return e;
}