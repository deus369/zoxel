#ifndef Zoxel_RenderingCore
#define Zoxel_RenderingCore
//! rendering core Module.

// rendering
//! Used to set the brightness of an entity.
zoxel_component(Brightness, float);
#include "components/Mesh.c"
#include "components/Material.c"
#include "components/TextureGPULink.c"
// systems
#include "systems/InstanceRender2DSystem.c"
#include "systems/RenderMaterial2DSystem.c"
// #include "systems/ParticleRenderSystem.c"
#include "systems/InstanceRender3DSystem.c"

//! The rendering core Sub Module.
/**
*   \todo CPU Meshes?
*/
void RenderingCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, RenderingCore);
    // printf("Initializing rendering core.");
    // components
    ECS_COMPONENT_DEFINE(world, Brightness);
    ECS_COMPONENT_DEFINE(world, Mesh);
    ECS_COMPONENT_DEFINE(world, Material);
    ECS_COMPONENT_DEFINE(world, TextureGPULink);
    // gpu destruction hooks
    ecs_set_hooks(world, Material, { .dtor = ecs_dtor(Material) });
    ecs_set_hooks(world, TextureGPULink, { .dtor = ecs_dtor(TextureGPULink) });
    // systems
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