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
#include "steam/test_steam_io.c"

#define get_asset_path(folder_path, filename) concat_file_path(resources_path, folder_path character_slash filename);

zox_begin_module(Files)
zox_define_tag(Asset)
#ifdef __WINE__
    zox_logg("  > inside wine\n")
    exit(0)
#endif
zoxel_end_module(Files)

#endif
