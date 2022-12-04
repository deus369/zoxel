#ifndef zoxel_rendering_core
#define zoxel_rendering_core
//! rendering core Module.

/*#ifndef maxMeshQueue
#define maxMeshQueue 1024
#endif*/

//! \todo Create a Cube with unique mesh - for chunk - add these components and update mesh for voxel chunk.
//      - Test Mesh - simply create a test entity now with mesh and set to dirty
//      - set data as cube and render
//      - Animate rotate the cube - for testing

// Tags
ECS_DECLARE(Mesh);
ECS_DECLARE(ElementRender);
// components
//! Used to set the brightness of an entity.
zoxel_component(Brightness, float);
zoxel_memory_component(MeshIndicies, int);
zoxel_memory_component(MeshVertices, float);
zoxel_memory_component(MeshUVs, float);
zoxel_state_component(MeshDirty);
#include "components/MaterialGPULink.c"
#include "components/TextureGPULink.c"
#include "components/mesh_gpu_link.c"
#include "components/uvs_gpu_link.c"
// #include "components/TextureCoordinatesGPULink.c"
zoxel_component(EternalRotation, float4);
// util
#include "util/mesh_util.c"
#include "util/render_util.c"
// prefabs
// systems
// animation systems
#include "systems/eternal_rotation_system.c"
// update systems
#include "systems/mesh_update_system.c"
#include "systems/mesh_uvs_update_system.c"
zoxel_reset_system(MeshDirtySystem, MeshDirty);
// render 2D systems
#include "render2D_systems/render2D_system.c"
#include "render2D_systems/render2D_mesh_system.c"
#include "render2D_systems/render2D_instance_system.c"
// render 3D systems
#include "render3D_systems/render3D_system.c"
#include "render3D_systems/render3D_uvs_system.c"
#include "render3D_systems/render3D_instance_system.c"
// util
#include "util/render_loop.c"



//! The rendering core Sub Module.
/**
*   \todo CPU Meshes?
*/
void RenderingCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, RenderingCore);
    // printf("Initializing rendering core.");
    ECS_TAG_DEFINE(world, Mesh);
    ECS_TAG_DEFINE(world, ElementRender);
    // components
    ECS_COMPONENT_DEFINE(world, Brightness);
    zoxel_memory_component_define(world, MeshIndicies);
    zoxel_memory_component_define(world, MeshVertices);
    zoxel_memory_component_define(world, MeshUVs);
    ECS_COMPONENT_DEFINE(world, MeshDirty);
    ECS_COMPONENT_DEFINE(world, MaterialGPULink);
    ECS_COMPONENT_DEFINE(world, TextureGPULink);
    ECS_COMPONENT_DEFINE(world, MeshGPULink);
    ECS_COMPONENT_DEFINE(world, UvsGPULink);
    // ECS_COMPONENT_DEFINE(world, TextureCoordinatesGPULink);
    ECS_COMPONENT_DEFINE(world, EternalRotation);
    // gpu destruction hooks
    ecs_set_hooks(world, MaterialGPULink, { .dtor = ecs_dtor(MaterialGPULink) });
    ecs_set_hooks(world, TextureGPULink, { .dtor = ecs_dtor(TextureGPULink) });
    ecs_set_hooks(world, MeshGPULink, { .dtor = ecs_dtor(MeshGPULink) });
    ecs_set_hooks(world, UvsGPULink, { .dtor = ecs_dtor(UvsGPULink) });
    // move this to animations systems
    zoxel_system(world, EternalRotationSystem, EcsOnUpdate, [out] Rotation, [in] EternalRotation);  // _main_thread
    // render2D
    zoxel_system_main_thread(world, InstanceRender2DSystem, 0,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink,
        [none] !MeshGPULink);
    zoxel_system_main_thread(world, RenderMaterial2DSystem, 0,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [in] MaterialGPULink,
        [in] TextureGPULink, [none] !MeshGPULink);
    zoxel_system_main_thread(world, RenderMeshMaterial2DSystem, 0,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [in] MeshGPULink,
        [in] MaterialGPULink, [in] TextureGPULink);
    // render3D
    zoxel_system_main_thread(world, Render3DSystem, 0, // EcsOnStore,
        [in] Position, [in] Rotation, [in] Scale1D, [in] Brightness,
        [in] MeshGPULink, [in] MaterialGPULink, [in] MeshIndicies,
        [none] !UvsGPULink);
    zoxel_system_main_thread(world, Render3DUvsSystem, 0, // EcsOnStore,
        [in] Position, [in] Rotation, [in] Scale1D, [in] Brightness,
        [in] MeshGPULink, [in] MaterialGPULink, [in] TextureGPULink, [in] MeshIndicies);
    zoxel_system_main_thread(world, InstanceRender3DSystem, 0,
        [in] Position, [in] Rotation, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink, [none] !MeshGPULink);
    // updates
    zoxel_system_main_thread(world, MeshUpdateSystem, EcsOnValidate,
        [in] MeshDirty,
        [in] MeshIndicies,[in] MeshVertices,
        [in] MeshGPULink, [in] MaterialGPULink,
        [none] !MeshUVs);
    zoxel_system_main_thread(world, MeshUvsUpdateSystem, EcsOnValidate,
        [in] MeshDirty, [in] MeshIndicies, [in] MeshVertices, [in] MeshUVs,
        [in] MeshGPULink, [in] MaterialGPULink);
    zoxel_reset_system_define(MeshDirtySystem, MeshDirty);
}

//set_mesh_indicies(world, e, cubeIndicies3, 12);
//set_mesh_vertices(world, e, cubeVertices3, 24);

// printf("instanceShader3D: %i %i\n", instanceShader3D.x, instanceShader3D.y);
/*const MeshIndicies *meshIndicies = ecs_get(world, e, MeshIndicies);
for (int j = 0; j < meshIndicies->length; j++)
{
    printf("    - (2) Index [%i] is [%i]\n", j, meshIndicies->value[j]);
}
const MeshVertices *meshVertices = ecs_get(world, e, MeshVertices);
for (int j = 0; j < meshVertices->length; j++)
{
    printf("    - (2) Vertex [%i] is [%fx%fx%f]\n", j, meshVertices->value[j].x, meshVertices->value[j].y, meshVertices->value[j].z);
}*///,
        //.move = ecs_move(MaterialGPULink),
        //.dtor = ecs_dtor(MaterialGPULink)
#endif