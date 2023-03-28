#ifndef zoxel_stats
#define zoxel_stats

zoxel_declare_user_data(Stat)
#include "prefabs/stat.c"

zoxel_begin_module(Stats)
zoxel_define_user_data(Stat)
spawn_prefab_stat(world);
zoxel_end_module(Stats)

#endif