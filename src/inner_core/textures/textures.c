#ifndef zoxel_textures
#define zoxel_textures

#include "core/textures_core.c"

void TexturesImport(ecs_world_t *world) {
    zoxel_module(textures)
    zoxel_import_module(TexturesCore)
}

// \todo Blueprints (Nodes) + UI
// \todo Noise generation to work on a node.
#endif