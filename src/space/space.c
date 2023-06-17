#ifndef zoxel_space
#define zoxel_space

#include "games/games.c"
#include "weathers/weathers.c"
#include "realms/realms.c"
#include "players/players.c"

void spawn_prefabs_space(ecs_world_t *world) {
    spawn_prefabs_players(world);
    spawn_prefabs_realms(world);
}

zox_begin_module(Space)
zox_import_module(Games)
zox_import_module(Weathers)
zox_import_module(Realms)
if (!headless) zox_import_module(Players)
zoxel_end_module(Space)

#endif