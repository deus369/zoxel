#ifndef zox_textures_io
#define zox_textures_io

zox_declare_tag(SaveTexture)
#include "systems/textures_save_system.c"
#include "util/texture_files.c"

void dispose_textures_io(ecs_world_t *world, void *ctx) {
    dispose_files_textures(world);
}

void initialize_textures_io(ecs_world_t *world) {
    load_files_textures(world);
}

zox_begin_module(TexturesIO)
zox_module_dispose(dispose_textures_io)
zox_define_tag(SaveTexture)
initialize_textures_io(world);
zoxel_end_module(TexturesIO)

#endif
