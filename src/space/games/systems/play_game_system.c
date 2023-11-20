/*void PlayGameSystem(ecs_iter_t *it) {
    zox_iter_world()
    const GenericEvent *genericEvents = ecs_field(it, GenericEvent, 1);
    for (int i = 0; i < it->count; i++) {
        const GenericEvent *genericEvent = &genericEvents[i];
        if (genericEvent->value == zoxel_event_play_game) play_game(world);
        zoxel_log(" > game play begins [%lu]\n", it->entities[i]);
    }
} zox_declare_system(PlayGameSystem)*/
