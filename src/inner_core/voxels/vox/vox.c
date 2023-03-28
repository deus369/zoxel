#ifndef zoxel_voxels_vox
#define zoxel_voxels_vox

// #define zoxel_debug_vox_read
zoxel_declare_tag(Vox)
#include "util/vox_read_util.c"
#include "prefabs/vox.c"
// #include "systems/noise_chunk_system.c"
#include "util/vox_files.c"

zoxel_begin_module(Vox)
zoxel_define_tag(Vox)
spawn_prefab_vox(world);
// load_vox_files();
zoxel_end_module(Vox)

#endif