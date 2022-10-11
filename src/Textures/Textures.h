//! Textures Module.
#ifndef Zoxel_Textures
#define Zoxel_Textures

// rendering
#include "Components/Texture.c"
// #include "Systems/TextureDirtySystem.c"  // if has material, update to material

void InitializeTextures(ecs_world_t *world)
{
    ECS_COMPONENT(world, Texture);
    // ECS_SYSTEM(world, RenderSystem, EcsOnUpdate, Position2D, Rotation2D, Scale2D, Brightness);
}

#endif