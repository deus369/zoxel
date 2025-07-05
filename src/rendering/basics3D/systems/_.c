#include "render3D_system.c"
#include "render3D_instance_system.c"
#include "render_characters3D_system.c"
#include "mesh_update_system.c"
#include "mesh_update_textured3D_system.c"
#include "mesh_update_characters3D_system.c"
#include "textured_render_system.c"
#ifndef zox_disable_rendering_instances
    #include "vox_instance_render_system.c"
#endif

void define_systems_basics3D(ecs_world_t *world) {
    // skybox
    zox_render3D_plus_system(Render3DSystem, [in] TransformMatrix, [in] Brightness, [in] MeshGPULink, [in] MeshIndicies, [in] MaterialGPULink, [none] MeshBasic3D)
    // unique textured meshes - items
    zox_render3D_plus_system(TexturedRenderSystem, [in] TransformMatrix, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] RenderDisabled, [in] MaterialGPULink, [in] TextureGPULink, [in] MaterialTextured3D, [none] TexturedMesh3D)
    // characters
    zox_render3D_plus_system(RenderCharacters3DSystem, [in] MeshIndicies, [in] MeshGPULink, [in] ColorsGPULink, [in] TransformMatrix, [in] RenderDisabled, [none] MeshColorRGBs, [none] !UvsGPULink, [none] rendering.core.RendererColored)
#ifndef zox_disable_rendering_instances
    zox_render3D_plus_system(VoxInstanceRenderSystem, [in] TransformMatrix, [in] InstanceLink, [in] RenderDisabled, [none] rendering.core.RendererInstance)
#endif
    // upload gpu
    zox_system_1(MeshUpdateSystem, zox_pip_mainthread, [in] MeshDirty, [in] MeshIndicies, [in] MeshVertices, [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshUVs, [none] !MeshColorRGBs)
    zox_system_1(Mesh3DTexturedUploadSystem, zox_pip_mainthread, [in] MeshIndicies, [in] MeshVertices, [in] MeshUVs, [in] MeshColorRGBs, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshDirty)
    zox_system_1(MeshUpdateCharacters3DSystem, zox_pip_mainthread, [in] MeshIndicies, [in] MeshVertices, [in] MeshColorRGBs, [in] MeshDirty, [out] MeshGPULink, [out] ColorsGPULink, [none] MeshColorRGBs, [none] !MeshUVs)
}

// zox_render3D_plus_system(Render3DSystem, [in] TransformMatrix, [in] Brightness, [in] MeshGPULink, [in] MeshIndicies, [in] MaterialGPULink, [none] !UvsGPULink, [none] !MeshColorRGBs, [none] !ColorsGPULink, [none] MeshBasic3D)
// idk
// zox_system_1(InstanceRender3DSystem, 0, [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink, [none] !MeshGPULink)