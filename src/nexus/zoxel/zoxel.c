#ifndef def_zox_game_zoxel
#define def_zox_game_zoxel

#ifndef zox_beta
const char *game_name = "zoxel";
#else
const char *game_name = "zoxel beta";
#endif
#include "util/boot.c"

void ZoxelImport(ecs_world_t *world) {
    zox_module(Zoxel)
    boot_event = boot_zoxel_game;
}

#endif
