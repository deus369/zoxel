entity spawn_prefab_element_textured(ecs *world,
    const entity prefab)
{
    zox_prefab_child(prefab)
    zox_prefab_name("element_textured")

    // frame texture
    zox_prefab_set(e, TextureDirty, { 0 });
    zox_add_tag(e, FrameTexture);
    zox_prefab_set(e, Seed, { 666 });
    zox_prefab_set(e, GenerateTexture, { zox_generate_texture_trigger });
    zox_prefab_set(e, FrameCorner, { default_button_corner });
    zox_prefab_set(e, OutlineThickness, { default_button_frame_thickness });
    zox_prefab_set(e, Color, { default_fill_color });
    zox_prefab_set(e, OutlineColor, { default_outline_color });

    return e;
}