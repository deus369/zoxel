ecs_entity_t icon_mouse_follow;

ecs_entity_t spawn_prefab_icon_mouse_follow(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_add_tag(e, Icon)
    zox_add_tag(e, IconTexture)  // general one
    zox_prefab_set(e, IconType, { 0 })
    zox_add_tag(e, MouseElement)
    zox_prefab_set(e, ZeviceLink, { 0 })
    zox_set(e, IconRadius, { default_icon_radius })
    zox_set(e, RenderDisabled, { 1 })
    return e;
}
