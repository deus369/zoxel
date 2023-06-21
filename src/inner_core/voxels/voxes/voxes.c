#ifndef zoxel_voxes
#define zoxel_voxes

zox_declare_tag(Vox)
#include "data/default_palette.c"
#include "data/vox_file.c"
#include "util/vox_read_util.c"
#include "util/vox_files.c"
#include "prefabs/vox.c"

void load_resources_voxes(ecs_world_t *world) {
    load_vox_files();
}

void spawn_prefabs_voxes(ecs_world_t *world) {
    spawn_prefab_vox(world);
}

zox_begin_module(Vox)
zox_define_tag(Vox)
zoxel_end_module(Vox)

#endif