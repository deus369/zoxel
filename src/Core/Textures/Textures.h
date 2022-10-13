//! Textures Module.
#ifndef Zoxel_Textures
#define Zoxel_Textures

// rendering
#include "Components/Texture.c"

ECS_COMPONENT_DECLARE(Texture);
// #include "Systems/TextureDirtySystem.c"  // if has material, update to material

void TexturesImport(ecs_world_t *world)
{
    ECS_MODULE(world, Textures);
    ECS_COMPONENT_DEFINE(world, Texture);
    // ECS_SYSTEM(world, Render2DSystem, EcsOnUpdate, Position2D, Rotation2D, Scale2D, Brightness);
}

#endif