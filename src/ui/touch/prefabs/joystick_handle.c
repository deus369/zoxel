entity spawn_prefab_virtual_joystick_pointer(ecs *world) {
    zox_prefab()
    zox_prefab_name("virtual_joystick_pointer")
    zox_add_tag(e, Button)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 4 })
    zox_prefab_set(e, OutlineThickness, { 4 })
    zox_prefab_set(e, Color, { virtual_joystick_pointer_color })
    add_ui_plus_components(world, e);
    return e;
}