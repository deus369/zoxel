#ifndef zox_textures_io
#define zox_textures_io

#define directory_textures "textures"character_slash
int files_count_textures = 0;
ecs_entity_t *files_textures;
zox_declare_tag(SaveTexture)
#include "systems/textures_save_system.c"
#include "util/texture_files.c"

void dispose_textures_io(ecs_world_t *world, void *ctx) {
    dispose_files_textures(world);
}

zox_begin_module(TexturesIO)
zox_module_dispose(dispose_textures_io)
zox_define_tag(SaveTexture)
load_files_textures(world);
zoxel_end_module(TexturesIO)

#endif
