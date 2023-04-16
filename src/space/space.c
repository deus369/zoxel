#ifndef zoxel_space
#define zoxel_space

#include "games/games.c"
#include "weathers/weathers.c"
#include "realms/realms.c"
#include "players/players.c"

zoxel_begin_module(Space)
zoxel_import_module(Games)
zoxel_import_module(Weathers)
zoxel_import_module(Realms)
if (!headless) zoxel_import_module(Players)
zoxel_end_module(Space)

#endif