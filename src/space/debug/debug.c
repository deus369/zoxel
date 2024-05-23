#if !defined(zox_mod_debug) && defined(zox_mod_players)
#define zox_mod_debug

#include "systems/game_debug_label_system.c"

void initialize_debug(ecs_world_t *world) { }

void spawn_prefabs_debug(ecs_world_t *world) { }

zox_begin_module(Debug)
zox_system(GameDebugLabelSystem, EcsOnStore, [out] ZextDirty, [out] ZextData, [none] game.u.i.GameDebugLabel)
spawn_prefabs_debug(world);
initialize_debug(world);
zoxel_end_module(Debug)

#endif
