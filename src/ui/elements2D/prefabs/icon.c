// a small square frame ui with an icon in it
// used for game - action/skill/stat - uis
ecs_entity_t spawn_prefab_icon(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("icon")
    zox_add_tag(e, Selectable)
    zox_prefab_set(e, SelectState, { zox_select_state_none })
    zox_add_tag(e, Clickable)
    zox_prefab_set(e, ClickState, { 0 })
    zox_prefab_set(e, Clicker, { 0 })
    zox_prefab_set(e, ClickEvent, { NULL })
    zox_add_tag(e, Icon)
    zox_add_tag(e, IconTexture)  // general one
    zox_prefab_set(e, IconType, { 0 })
    zox_prefab_set(e, IconIndex, { 0 })
    zox_prefab_set(e, ParentLink, { 0 })
    zox_prefab_set(e, Color, { default_fill_color_icon })
    zox_prefab_set(e, OutlineColor, { default_outline_color_icon })
    zox_prefab_set(e, IconRadius, { default_icon_radius })
    zox_prefab_set(e, Children, { 0, NULL });
    return e;
}