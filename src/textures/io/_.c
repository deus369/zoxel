#ifndef zoxm_textures_io
#define zoxm_textures_io

#define directory_textures "textures"
int files_count_textures = 0;
ecs_entity_t *files_textures;
string_hashmap *files_hashmap_textures;
zox_declare_tag(SaveTexture)
#include "prefabs/file_texture.c"
#include "systems/textures_save_system.c"
#include "util/texture_files.c"

void dispose_textures_io(ecs_world_t *world, void *ctx) {
    dispose_files_textures();
}

zox_begin_module(TexturesIO)
    zox_module_dispose(dispose_textures_io)
    zox_define_tag(SaveTexture)
    add_hook_files_load(load_files_textures);
zox_end_module(TexturesIO)

#endif