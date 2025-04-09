// extern ecs_entity_t spawn_statbar2D(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent, const ecs_entity_t player, const ecs_entity_2 character_group);

ecs_entity_t spawn_prefab_menu_game(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("game_ui")
    zox_add_tag(e, MenuGame)
    zox_prefab_set(e, AnchorSize, { float2_one })
    zox_prefab_add(e, Children)
    return e;
}

extern void spawn_menu_game_stats(ecs_world_t *world, const ecs_entity_t menu_game, const ecs_entity_t player, Children *children);

ecs_entity_t spawn_menu_game(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t player) {
    // , const ecs_entity_2 character_group, const ecs_entity_t canvas
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t e = spawn_element_invisible_on_canvas(world, prefab, canvas, int2_zero, canvas_size, float2_half);
    zox_name("game_ui")
    Children *children = &((Children) { 0, NULL });
    // zox_get_muter(e, Children, game_ui_children)
    add_to_Children(children, spawn_crosshair(world, canvas, e));
    // spawn character uis too
#ifndef zox_disable_statbars
    spawn_menu_game_stats(world, e, player, children);
#endif
    zox_set(e, Children, { children->length, children->value })
    return e;
}

void dispose_menu_game(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuGame, game_ui)
    if (game_ui) zox_delete(game_ui)
    dispose_game_menu_touch(world, canvas);
}
