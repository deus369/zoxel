void PlayGameButtonSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const ClickableState *clickableStates = ecs_field(it, ClickableState, 2);
    for (int i = 0; i < it->count; i++) {
        const ClickableState *clickableState = &clickableStates[i];
        if (clickableState->value == 1) {
            const ParentLink *parentLink = ecs_get(world, it->entities[i], ParentLink);
            ecs_entity_t window = parentLink->value;
            ecs_delete(it->world, window);
            spawn_generic_event(it->world, zoxel_event_play_game);
        }
    }
}
zoxel_declare_system(PlayGameButtonSystem)