/**
 *  Zox Files
 *
 *      - Zox Files functions
 *
 *      - todo: move to core
 *      - todo: remove sdl use and just make my own functions
 *
 * */
#ifndef zox_files
#define zox_files

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "data/file_list.c"
// used for file io functions
zox_declare_tag(Asset)
#include "util/path_util.c"
#include "util/directory_util.c"
#include "util/saves.c"
#include "util/io_macros.c"
#include "util/realm_save.c"
#include "steam/test_steam_io.c"

#define get_asset_path(folder_path, filename) concat_file_path(resources_path, folder_path character_slash filename);

zox_begin_module(Files)
    zox_define_tag(Asset)
    if (initialize_pathing() == EXIT_FAILURE) {
        zox_log(" ! FAILED PATHING\n")
        return;
    }
    #ifdef __WINE__
        zox_log("  > inside wine\n")
        exit(0)
    #endif
zoxel_end_module(Files)

#endif
