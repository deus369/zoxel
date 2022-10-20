#ifndef Zoxel_Textures
#define Zoxel_Textures
//! Textures Module.
/**
 * \todo Blueprints (Nodes) + UI
 * \todo Noise generation to work on a node.
*/

// Components
#include "Core/TexturesCore.c"

void TexturesImport(ecs_world_t *world)
{
    ECS_MODULE(world, Textures);
    ECS_IMPORT(world, TexturesCore);
}

#endif