// a small square frame ui with an icon in it
// used for game - action/skill/stat - uis
entity spawn_prefab_frame(
    ecs *world,
    const entity prefab
) {
    zox_prefab_child(prefab);
    zox_prefab_name("frame");
    zox_add_tag(e, Frame);
    zox_prefab_set(e, Color, { default_fill_color_frame });
    zox_prefab_set(e, OutlineColor, { default_outline_color_frame });
    zox_prefab_set(e, Children, { 0, NULL });
    return e;
}