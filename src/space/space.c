#ifndef zoxel_space
#define zoxel_space

#include "weathers/weathers.c"
#include "realms/realms.c"
#include "games/games.c"
#if defined(zoxel_include_players)
    #include "players/players.c"
#endif

void spawn_prefabs_space(ecs_world_t *world) {
    spawn_prefabs_weather(world);
    spawn_prefabs_realms(world);
    spawn_prefabs_games(world);
#if defined(zoxel_include_players)
    if (!headless) {
        spawn_prefabs_players(world);
        zox_prefab_set(prefab_game, PlayerLinks, { 0, NULL })
    }
#endif
}

void dispose_space(ecs_world_t *world) {
    dispose_games(world);
}

void initialize_space(ecs_world_t *world) {
    initialize_games(world);
    initialize_players(world);
}

zox_begin_module(Space)
zox_import_module(Weathers)
zox_import_module(Realms)
zox_import_module(Games)
#if defined(zoxel_include_players)
if (!headless) zox_import_module(Players)
#endif
zoxel_end_module(Space)

#endif
