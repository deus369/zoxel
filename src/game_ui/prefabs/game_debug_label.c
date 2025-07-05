const color debug_color_outline = (color) { 0, 255, 0, 255 }; // { 76, 66, 133, 255 };
const color debug_color_fill = (color) { 0, 255, 0, 255 }; // { 132, 177, 212, 255 };

// sets update function
void set_prefab_debug_label(ecs_world_t *world, DebugLabelEvent value) {
    if (!zox_valid(prefab_game_debug_label)) {
        zox_log_error("prefab_game_debug_label has not spawned yet")
        return;
    }
    zox_set(prefab_game_debug_label, DebugLabelData, { value })
}

ecs_entity_t spawn_prefab_game_debug_label(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_add_tag(e, GameDebugLabel)
    // zox_prefab_set(e, QuadsCount, { 0 })
    prefab_set_mesh2D_vertices(world, e, square_vertices_top_right_aligned, 4);
    prefab_game_debug_label = e;
    zox_prefab_add(e, PlayerLink)
    zox_prefab_add(e, DebugLabelData)
    return e;
}

ecs_entity_t spawn_game_debug_label(ecs_world_t *world, const ecs_entity_t canvas) {
    if (!canvas || !zox_has(canvas, PlayerLink)) {
        zox_log("! [spawn_game_debug_label] error: invalid canvas, or no player found on canvas\n")
        return 0;
    }
    const ecs_entity_t parent = canvas;
    const int layer = 1;
    const byte font_size = 16;
    const byte2 padding = (byte2) { 12, 8 };
    const byte alignment = zox_mesh_alignment_top_right;
    const float2 anchor = float2_one; //  { 1.0f, 1.0f };
    const int2 pixel_position = (int2) { -8, -8 };
    const int2 parent_pixel_size = zox_get_value(parent, PixelSize)
    // returns the child zext
    const ecs_entity_t zext = spawn_label_background(world, prefab_game_debug_label, parent, canvas, pixel_position, anchor, padding, "", font_size, alignment, layer, int2_half(parent_pixel_size), parent_pixel_size, debug_color_outline, debug_color_fill, 0);
    zox_geter(canvas, PlayerLink, playerLink)
    zox_set(zext, PlayerLink, { playerLink->value })
    return zext;
}