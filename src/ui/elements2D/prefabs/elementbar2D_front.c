entity spawn_prefab_elementbar2D_front(ecs *world) {
    zox_prefab()
    zox_prefab_name("elementbar2D_front")
    zox_add_tag(e, FillTexture)
    add_ui_plus_components(world, e);
    zox_prefab_set(e, Color, { front_bar_color })
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, MeshAlignment, { zox_mesh_alignment_left })
    return e;
}