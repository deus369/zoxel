#ifndef zox_files
#define zox_files

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
// used for file io functions
// zox_declare_tag(Files)
// #include "prefabs/terminal.c"
#include "util/path_util.c"
#include "util/directory_util.c"
#include "steam/test_steam_io.c"

void spawn_prefabs_files(ecs_world_t *world) {
    // spawn_prefab_filemanager(world);
#ifdef __WINE__
    zox_logg("  > inside wine\n")
    exit(0)
#endif
}

zox_begin_module(Files)
spawn_prefabs_files(world);
zoxel_end_module(Files)

#endif
