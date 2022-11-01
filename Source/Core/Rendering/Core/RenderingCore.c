#ifndef Zoxel_RenderingCore
#define Zoxel_RenderingCore
//! Rendering Core Module.

// Rendering
#include "Components/Brightness.c"
#include "Components/Mesh.c"
#include "Components/Material.c"
#include "Components/TextureGPULink.c"
// Systems
#include "Systems/InstanceRender2DSystem.c"
#include "Systems/RenderMaterial2DSystem.c"
// #include "Systems/ParticleRenderSystem.c"
#include "Systems/InstanceRender3DSystem.c"

//! The Rendering Core Sub Module.
/**
*   \todo CPU Meshes?
*/
void RenderingCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, RenderingCore);
    // printf("Initializing Rendering Core.");
    // Components
    ECS_COMPONENT_DEFINE(world, Brightness);
    ECS_COMPONENT_DEFINE(world, Mesh);
    ECS_COMPONENT_DEFINE(world, Material);
    ECS_COMPONENT_DEFINE(world, TextureGPULink);
    // gpu destruction hooks
    ecs_set_hooks(world, Material, { .dtor = ecs_dtor(Material) });
    ecs_set_hooks(world, TextureGPULink, { .dtor = ecs_dtor(TextureGPULink) });
    // Systems
    ECS_SYSTEM_DEFINE(world, InstanceRender2DSystem, 0,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [none] !Material);
    ECS_SYSTEM_DEFINE(world, RenderMaterial2DSystem, 0,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [in] Material, [in] TextureGPULink);
    //ECS_SYSTEM_DEFINE(world, ParticleRenderSystem, 0,
    //    [in] Position, [in] Rotation, [in] Scale1D, [in] Brightness, [none] !Material);
    ECS_SYSTEM_DEFINE(world, InstanceRender3DSystem, 0,
        [in] Position, [in] Rotation, [in] Scale1D, [in] Brightness, [none] !Material);
}
#endif