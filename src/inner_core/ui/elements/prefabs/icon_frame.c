// a small square frame ui with an icon in it
// used for game - action/skill/stat - uis
ecs_entity_t spawn_prefab_icon_frame(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_frame")
    zox_add_tag(e, IconFrame)
    zox_prefab_set(e, Children, { 0, NULL })
    return e;
}
