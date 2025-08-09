#ifndef zox_disable_player_character3D
byte game_rule_attach_to_character = 1;
#else
byte game_rule_attach_to_character = 0;
#endif
// extern byte game_rule_attach_to_character;
void process_arguments_games(ecs_world_t *world, char* args[], int count) {
    (void) world;
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--freeroam") == 0) {
            game_rule_attach_to_character = 0;
        }
    }
}