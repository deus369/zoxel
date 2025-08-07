entity spawn_prefab_label_background(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("label_background")
    add_ui_plus_components(world, e);
    zox_add_tag(e, Label)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Color, {{ 35, 88, 66, 255 }})
    return e;
}