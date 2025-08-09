entity spawn_prefab_window(ecs *world, const entity prefab) {
    zox_prefab_child(prefab);
    zox_prefab_name("window");
    // interaction
    zox_add_tag(e, BoundToCanvas);
    zox_add_tag(e, Selectable);
    zox_prefab_set(e, DraggableLimits, { int4_zero });
    // Window
    zox_add_tag(e, Window);
    zox_add_tag(e, WindowRaycastTarget);
    zox_prefab_set(e, HeaderHeight, { 0 });
    zox_prefab_set(e, WindowLayer, { 0 });
    zox_prefab_set(e, SetWindowLayer, { 0 });
    // zox_prefab_add(e, Children)
    zox_prefab_set(e, Children, { 0 });
    // text properties used for spawning list  elements
    zox_prefab_set(e, ElementFontSize, { default_font_size });
    // set
    zox_set(e, FrameCorner, { default_window_corner });
    zox_set(e, Color, { window_fill });
    zox_set(e, OutlineColor, { window_outline });
    return e;
}