ecs_entity_t spawn_prefab_menu_game(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("game_ui")
    zox_add_tag(e, MenuGame)
    zox_prefab_set(e, AnchorSize, { float2_one })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_menu_game(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t player, const ecs_entity_2 character_group, const ecs_entity_t canvas) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t e = spawn_element_invisible_on_canvas(world, prefab, canvas, int2_zero, canvas_size, float2_half);
    zox_name("game_ui")
    zox_get_muter(e, Children, game_ui_children)
    add_to_Children(game_ui_children, spawn_crosshair(world, canvas, e));
#ifndef zox_disable_statbars
    add_to_Children(game_ui_children, spawn_statbar2D(world, canvas, e, player, character_group));
#endif
    return e;
}

void dispose_menu_game(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuGame, game_ui)
    if (game_ui) zox_delete(game_ui)
    else zox_log(" ! no MenuGame found\n")
    dispose_game_menu_touch(world, canvas);
}
