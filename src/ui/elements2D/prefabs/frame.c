// a small square frame ui with an icon in it
// used for game - action/skill/stat - uis
ecs_entity_t spawn_prefab_frame(
    ecs_world_t *world,
    const ecs_entity_t prefab
) {
    zox_prefab_child(prefab);
    zox_prefab_name("frame");
    zox_add_tag(e, Frame);
    zox_prefab_set(e, Color, { default_fill_color_frame });
    zox_prefab_set(e, OutlineColor, { default_outline_color_frame });
    zox_prefab_set(e, Children, { 0, NULL });
    return e;
}