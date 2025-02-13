ecs_entity_t spawn_prefab_tooltip(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_add_tag(e, Tooltip)
    zox_add_tag(e, ZextRenderEnabler)
    zox_prefab_set(e, RenderDisabled, { 1 })
    zox_prefab_set(e, MeshAlignment, { zox_mesh_alignment_top_right })
    // prefab_set_mesh2D_vertices(world, e, square_vertices_top_right_aligned, 4);
    add_mouse_follow_components(world, e);
    zox_prefab_set(e, ZeviceLink, { 0 })
    return e;
}

ecs_entity_t spawn_tooltip(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas) {
    const ecs_entity_t parent = canvas;
    const int layer = max_layers2D - 2;
    const byte font_size = 20;
    const byte2 padding = (byte2) { 12, 8 };
    const byte alignment = zox_mesh_alignment_top_right;
    const float2 anchor = float2_one;
    const int2 pixel_position = (int2) { -8, -8 };
    const int2 parent_pixel_size = zox_get_value(parent, PixelSize)
    const color debug_color_outline = (color) { 76, 66, 133, 255 };
    const color debug_color_fill = (color) { 122, 122, 122, 255 };
    const ecs_entity_t e = spawn_label_background(world, prefab, parent, canvas, pixel_position, anchor, padding, "", font_size, alignment, layer, int2_half(parent_pixel_size), parent_pixel_size, debug_color_outline, debug_color_fill, 1);
    if (mouse_entity) {
        zox_geter(mouse_entity, Children, zevices)
        zox_set(e, ZeviceLink, { zevices->value[0] })
    }
    return e;
}
