#ifndef zoxel_voxes
#define zoxel_voxes

zoxel_declare_tag(Vox)
#include "data/default_palette.c"
#include "data/vox_file.c"
#include "util/vox_read_util.c"
#include "util/vox_files.c"
#include "prefabs/vox.c"

zoxel_begin_module(Vox)
zoxel_define_tag(Vox)
spawn_prefab_vox(world);
load_vox_files();
zoxel_end_module(Vox)

#endif