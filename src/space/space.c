#ifndef zox_mod_space
#define zox_mod_space

#include "weathers/weathers.c"
#include "realms/realms.c"
#include "players/players.c"
#include "debug/debug.c"

zox_begin_module(Space)
zox_import_module(Weathers)
zox_import_module(Realms2)
#if defined(zox_mod_players)
if (!headless) zox_import_module(Players2)
#endif
#if defined(zox_mod_debug)
zox_import_module(Debug)
#endif
zoxel_end_module(Space)

#endif
