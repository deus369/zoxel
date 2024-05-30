#if !defined(zox_mod_debug) && defined(zox_mod_players)
#define zox_mod_debug

#include "data/settings.c"
#include "systems/game_debug_label_system.c"

zox_begin_module(Debug)
zox_system(GameDebugLabelSystem, EcsOnStore, [out] ZextDirty, [out] ZextData, [none] game.u.i.GameDebugLabel)
zoxel_end_module(Debug)

#endif
