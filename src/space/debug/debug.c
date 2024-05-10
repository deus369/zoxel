#ifndef zox_module_debug
#define zox_module_debug

#include "systems/game_debug_label_system.c"

void initialize_debug(ecs_world_t *world) { }

void spawn_prefabs_debug(ecs_world_t *world) { }

zox_begin_module(Debug)
zox_system(GameDebugLabelSystem, EcsOnUpdate, [out] ZextDirty, [out] ZextData, [none] game.u.i.GameDebugLabel)
zoxel_end_module(Debug)

#endif
