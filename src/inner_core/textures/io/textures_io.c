#ifndef zoxel_textures_io
#define zoxel_textures_io

zox_declare_tag(SaveTexture)
#include "systems/textures_save_system.c"
#include "util/texture_files.c"

void dispose_resources_textures_io(ecs_world_t *world) {
    dispose_files_textures(world);
}

void load_resources_textures_io(ecs_world_t *world) {
    load_files_textures(world);
}

zox_begin_module(TexturesIO)
zox_define_tag(SaveTexture)
zoxel_end_module(TexturesIO)

#endif
