// just a panel with a label and a bar
// the bar can be clicked to reposition the handle as well
entity spawn_prefab_slider(ecs *world, const entity prefab) {
    zox_prefab_child(prefab);
    zox_prefab_name("slider");
    // slider
    zox_prefab_add(e, SliderLabel);
    // transforms
    zox_prefab_set(e, ParentLink, { 0 });
    // set t texture data
    zox_set(e, FrameCorner, { default_button_corner });
    zox_set(e, OutlineThickness, { default_button_frame_thickness });
    zox_set(e, Color, { default_fill_color });
    zox_set(e, OutlineColor, { default_outline_color });
    return e;
}