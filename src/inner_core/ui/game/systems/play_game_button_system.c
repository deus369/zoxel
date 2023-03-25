//! Closes the game when button is clicked.
void PlayGameButtonSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    // printf("WindowCloseSystem [%i]\n", it->count);
    const ClickableState *clickableStates = ecs_field(it, ClickableState, 2);
    for (int i = 0; i < it->count; i++) {
        const ClickableState *clickableState = &clickableStates[i];
        if (clickableState->value == 1) {
            // destroy ui
            //! window is 2nd parent
            const ParentLink *parentLink = ecs_get(world, it->entities[i], ParentLink);
            // const ParentLink *parentParentLink = ecs_get(it->world, parentLink->value, ParentLink);
            ecs_entity_t window = parentLink->value;
            delete_hierarchy(world, window);
            // ecs_delete(it->world, window);
            // create play game event
            spawn_generic_event(it->world, 1);
        }
    }
}
zoxel_declare_system(PlayGameButtonSystem)