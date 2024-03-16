#ifndef def_zox_game_zoxel
#define def_zox_game_zoxel

#include "util/boot.c"

void ZoxelImport(ecs_world_t *world) {
    zox_module(Zoxel)
    boot_event = boot_zoxel_game;
    zox_game_type = zox_game_mode_3D;
}

#endif
