entity spawn_prefab_virtual_joystick(ecs *world) {
    zox_prefab()
    zox_prefab_name("virtual_joystick")
    zox_add_tag(e, JoystickUI)
    zox_add_tag(e, Button)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 2 })
    zox_prefab_set(e, OutlineThickness, { 2 })
    zox_prefab_set(e, Color, { virtual_joystick_color })
    zox_prefab_set(e, Children, { 0, NULL });
    add_ui_plus_components(world, e);
    zox_prefab_add(e, ZeviceLink)
    return e;
}