#ifndef zoxm_shaders
#define zoxm_shaders

byte is_log_shaders = 0;
#define directory_shaders "shaders"
int files_count_shaders = 0;
entity *files_shaders;
string_hashmap *files_hashmap_shaders;
entity prefab_file_shader;
// zox_tag(Shader)
zoxc_arrayd(ShaderSource, char)
#include "prefabs/file_shader.c"
#include "util/_.c"

void dispose_shaders(ecs *world, void *ctx) {
    (void) world;
    (void) ctx;
    dispose_files_shaders();
}

zox_begin_module(Shaders)
    zox_define_memory_component(ShaderSource);
    // zox_define_tag(Shader)
    zox_module_dispose(dispose_shaders);
    // add_hook_files_load(load_files_shaders);
    prefab_file_shader = spawn_prefab_file_shader(world);
zox_end_module(Shaders)

#endif