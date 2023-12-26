// i should just set new game state to playing here
extern void play_game(ecs_world_t *world, ecs_entity_t game);
extern void end_game(ecs_world_t *world, ecs_entity_t game);
extern ecs_entity_t main_menu;
extern ecs_entity_t local_game;

void button_event_play_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    // todo: link ui to game entity
    zox_delete_and_set(main_menu)
    play_game(world, local_game);
}

void button_event_end_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    end_game(world, local_game);
}
