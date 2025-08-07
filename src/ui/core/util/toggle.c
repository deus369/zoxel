entity player_toggle_ui(ecs *world,
    const entity player,
    const entity e,
    entity (*spawn_ui)(ecs*, const entity))
{
    if (e == 0) {
        return (*spawn_ui)(world, player);
    } else {
        zox_delete(e)
        return 0;
    }
}

entity player_toggle_ui_id(ecs *world,
    const entity player,
    const ElementLinks* elements,
    const entity id,
    entity (*spawn_ui)(ecs*, const entity))
{
    entity e = find_array_element_with_id(world,
        elements->value,
        elements->length,
        id);
    return player_toggle_ui(world, player, e, spawn_ui);
}

entity toggle_ui_with_id(ecs *world,
    entity (*spawn_ui)(ecs*, const entity),
    const entity id,
    const entity player)
{
    const entity canvas = zox_get_value(player, CanvasLink)
    find_child_with_id(canvas, id, ui)
    return player_toggle_ui(world, player, ui, spawn_ui);
}

#define toggle_ui_with_tag_e(spawn_ui, tag, e) {\
    find_child_with_tag(canvas, tag, ui)\
    player_toggle_ui(world, e, ui, spawn_ui);\
}

#define toggle_ui_with_tag(spawn_ui, tag) {\
    find_child_with_tag(canvas, tag, ui)\
    player_toggle_ui(world, canvas, ui, spawn_ui);\
}

void toggle_ui(ecs *world, const entity canvas, entity *e, entity (*spawn_ui)(ecs*, const entity)) {
    if (*e == 0) {
        const entity e2 = (*spawn_ui)(world, canvas);
        *e = e2;
    } else {
        zox_delete(*e)
        *e = 0;
    }
}