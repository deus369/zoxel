ecs_entity_t toggle_ui2(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t e, ecs_entity_t (*spawn_ui)(ecs_world_t*, const ecs_entity_t)) {
    if (e == 0) {
        return (*spawn_ui)(world, player);
    } else {
        zox_delete(e)
        return 0;
    }
}

ecs_entity_t toggle_ui_with_id(ecs_world_t *world, ecs_entity_t (*spawn_ui)(ecs_world_t*, const ecs_entity_t), const ecs_entity_t id, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_id(canvas, id, ui)
    return toggle_ui2(world, player, ui, spawn_ui);
}

#define toggle_ui_with_tag_e(spawn_ui, tag, e) {\
    find_child_with_tag(canvas, tag, ui)\
    toggle_ui2(world, e, ui, spawn_ui);\
}

#define toggle_ui_with_tag(spawn_ui, tag) {\
    find_child_with_tag(canvas, tag, ui)\
    toggle_ui2(world, canvas, ui, spawn_ui);\
}

void toggle_ui(ecs_world_t *world, const ecs_entity_t canvas, ecs_entity_t *e, ecs_entity_t (*spawn_ui)(ecs_world_t*, const ecs_entity_t)) {
    if (*e == 0) {
        const ecs_entity_t e2 = (*spawn_ui)(world, canvas);
        *e = e2;
    } else {
        zox_delete(*e)
        *e = 0;
    }
}