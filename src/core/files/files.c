#ifndef zoxel_files
#define zoxel_files

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
// used for file io functions
// todo:
//  > read/write async bytes to files (for multi threaded systems use)
// zoxel_settings
// zoxel_component_includes
// zox_declare_tag(Files)
// zoxel_prefab_includes
// #include "prefabs/terminal.c"
// zoxel_util_includes
#include "util/path_util.c"
#include "util/directory_util.c"

void spawn_prefabs_files(ecs_world_t *world) {
    // spawn_prefab_filemanager(world);
#ifdef __WINE__
    zox_logg("  > inside wine\n")
    exit(0)
#endif
}

zox_begin_module(Files)
// zoxel_component_defines
// zox_define_tag(Terminal)
// zoxel_system_defines
zoxel_end_module(Files)

#endif
