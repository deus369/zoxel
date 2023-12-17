#ifndef zoxel_textures
#define zoxel_textures

#include "core/textures_core.c"
#include "../../core/apps/sdl/textures/textures.c"
#include "io/textures_io.c"

void dispose_resources_textures(ecs_world_t *world) {
    dispose_resources_textures_io(world);
}

void load_resources_textures(ecs_world_t *world) {
    load_resources_textures_io(world);
}

zox_begin_module(Textures)
zox_import_module(TexturesCore)
zox_import_module(AppsTextures)
zox_import_module(TexturesIO)
zoxel_end_module(Textures)

// \todo Blueprints (Nodes) + UI
// \todo Noise generation to work on a node

#endif
