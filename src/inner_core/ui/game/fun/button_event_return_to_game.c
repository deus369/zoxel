#ifdef zoxel_include_players
    extern void toggle_pause_ui(ecs_world_t *world);
#endif

void button_event_return_to_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    // const ParentLink *parentLink = ecs_get(world, trigger_entity, ParentLink);
    // zox_delete(parentLink->value) // destroy main menu
    // zox_delete(pause_ui)
    #ifdef zoxel_include_players
        toggle_pause_ui(world);
    #endif
}