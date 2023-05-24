#ifndef zoxel_stats
#define zoxel_stats

zox_declare_user_data(Stat)
#include "prefabs/stat.c"

zox_begin_module(Stats)
zox_define_user_data(Stat)
spawn_prefab_stat(world);
zoxel_end_module(Stats)

#endif