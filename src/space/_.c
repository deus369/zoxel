#ifndef zoxm_space
#define zoxm_space

// one day we will actually make this abuot space
zox_declare_tag(Planet);
zox_declare_tag(Asteroid);
zox_declare_tag(Star);
#include "util/_.c"
#include "game/_.c"

void on_boot_space(ecs_world_t* world, ecs_entity_t app) {
    // move to game ui??
    spawn_players_cameras_canvases(world, players_playing, app);
    spawn_players_start_ui(world);
}

zox_begin_module(Space)
    zox_define_tag(Planet);
    zox_define_tag(Asteroid);
    zox_define_tag(Star);

    add_to_event_game_state((zox_game_event) { &players_game_state });
    add_hook_on_boot(on_boot_space);

zox_end_module(Space)

#endif