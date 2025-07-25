extern void spawn_menu_game_stats(ecs_world_t *world, const ecs_entity_t menu_game, const ecs_entity_t player, Children *children);

ecs_entity_t spawn_prefab_menu_game(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("menu_game")
    zox_add_tag(e, MenuGame)
    zox_prefab_set(e, AnchorSize, { float2_one })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_menu_game(ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t player,
    const ecs_entity_t character)
{
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    // make layout2 instead of element_invisible
    const ecs_entity_t e = spawn_element_invisible_on_canvas(world,
        prefab,
        canvas,
        int2_zero,
        canvas_size,
        float2_half);
    zox_name("menu_game")
    Children children = (Children) { 0, NULL };

    const ecs_entity_t crosshair = spawn_crosshair(world,
        (CanvasSpawnData) {
            .e = canvas,
            .size = canvas_size,
        },
        (ParentSpawnData) {
            .e = e,
            .position = int2_zero,
            .size = canvas_size,
        },
        (ElementSpawnData) {
            .prefab = prefab_crosshair,
            .layer = 1,
            .anchor = float2_half,
            .position = int2_zero,
            .size = crosshair_pixel_size,
            .texture_size = crosshair_texture_size,
        });

    add_to_Children(&children, crosshair);

    spawn_menu_game_stats(world, e, player, &children);

    zox_set_ptr(e, Children, children)
    // link to character
    zox_get_muter(character, ElementLinks, elementLinks)
    add_to_ElementLinks(elementLinks, e);
    zox_set(e, ElementHolder, { character })

    local_menu_game = e;
    return e;
}

void dispose_menu_game(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuGame, game_ui)
    if (game_ui) {
        zox_delete(game_ui)
    }
    dispose_menu_game_touch(world, player);
}