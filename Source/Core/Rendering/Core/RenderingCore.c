#ifndef Zoxel_RenderingCore
#define Zoxel_RenderingCore
// Rendering
#include "Components/Brightness.c"
#include "Components/Mesh.c"
#include "Components/Material.c"
// Systems
#include "Systems/Render2DSystem.c"

//! The Rendering Core Sub Module.
/**
*   \todo CPU Meshes?
*/
void RenderingCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, RenderingCore);
    // printf("Initializing Rendering Core.");
    ECS_COMPONENT_DEFINE(world, Brightness);
    ECS_COMPONENT_DEFINE(world, Mesh);
    ECS_COMPONENT_DEFINE(world, Material);
    ECS_SYSTEM_DEFINE(world, Render2DSystem, 0, [in] Position2D, [in] Rotation2D, [in] Scale2D, [in] Brightness, [none] !Material);
    ECS_SYSTEM_DEFINE(world, RenderMaterial2DSystem, 0, [in] Position2D, [in] Rotation2D, [in] Scale2D, [in] Brightness, [in] Material);
}
#endif