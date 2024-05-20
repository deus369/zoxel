#ifndef zox_space
#define zox_space

#include "weathers/weathers.c"
#include "realms/realms.c"
#if defined(zoxel_include_players)
#include "players/players.c"
#endif
#include "debug/debug.c"

void spawn_prefabs_space(ecs_world_t *world) {
    spawn_prefabs_weather(world);
    spawn_prefabs_realms2(world);
#if defined(zoxel_include_players)
    if (!headless) {
        spawn_prefabs_players(world);
        zox_prefab_set(prefab_game, PlayerLinks, { 0, NULL })
    }
#endif
}

void dispose_space(ecs_world_t *world) { }

void initialize_space(ecs_world_t *world) {
    initialize_realms2(world);
    initialize_players(world);
    initialize_debug(world);
}

zox_begin_module(Space)
zox_import_module(Weathers)
zox_import_module(Realms2)
#if defined(zoxel_include_players)
if (!headless) zox_import_module(Players)
#endif
zox_import_module(Debug)
zoxel_end_module(Space)

#endif
