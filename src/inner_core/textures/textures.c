#ifndef zoxel_textures
#define zoxel_textures

#include "core/textures_core.c"
#include "../../core/apps/sdl/textures/textures.c"
#include "io/textures_io.c"

void dispose_textures(ecs_world_t *world) {
    dispose_textures_io(world);
}

void initialize_textures(ecs_world_t *world) {
    initialize_textures_io(world);
}

void spawn_prefabs_textures(ecs_world_t *world) {
    spawn_prefabs_textures_core(world);
}

zox_begin_module(Textures)
zox_import_module(TexturesCore)
zox_import_module(AppsTextures)
zox_import_module(TexturesIO)
zoxel_end_module(Textures)

#endif
