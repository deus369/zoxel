#ifndef zoxel_textures
#define zoxel_textures
//! textures Module.
/**
 * \todo Blueprints (Nodes) + UI
 * \todo Noise generation to work on a node.
*/

// components
#include "core/textures_core.c"

void TexturesImport(ecs_world_t *world)
{
    ECS_MODULE(world, textures);
    ECS_IMPORT(world, TexturesCore);
}
#endif