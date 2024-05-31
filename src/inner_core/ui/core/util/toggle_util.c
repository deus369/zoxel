void toggle_ui2(ecs_world_t *world, const ecs_entity_t e2, const ecs_entity_t e, ecs_entity_t (*spawn_ui)(ecs_world_t*, const ecs_entity_t)) {
    if (e == 0) {
        (*spawn_ui)(world, e2);
    } else {
        zox_delete(e)
    }
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
