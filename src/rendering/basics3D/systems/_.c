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
    zox_render3D_plus_system(Render3DSystem,
        [in] transforms3.TransformMatrix,
        [in] rendering.Brightness,
        [in] rendering.core.MeshGPULink,
        [in] rendering.core.MeshIndicies,
        [in] rendering.core.MaterialGPULink,
        [none] MeshBasic3D)
    // unique textured meshes - items
    zox_render3D_plus_system(TexturedRenderSystem,
        [in] transforms3.TransformMatrix,
        [in] rendering.core.MeshGPULink,
        [in] rendering.core.UvsGPULink,
        [in] rendering.core.ColorsGPULink,
        [in] rendering.core.MeshIndicies,
        [in] rendering.RenderDisabled,
        [in] rendering.core.MaterialGPULink,
        [in] rendering.core.TextureGPULink,
        [in] MaterialTextured3D,
        [none] TexturedMesh3D)
    // characters
    zox_render3D_plus_system(RenderCharacters3DSystem,
        [in] rendering.core.MeshIndicies,
        [in] rendering.core.MeshGPULink,
        [in] rendering.core.ColorsGPULink,
        [in] transforms3.TransformMatrix,
        [in] rendering.RenderDisabled,
        [none] rendering.core.MeshColorRGBs,
        [none] !rendering.core.UvsGPULink,
        [none] rendering.core.RendererColored)
#ifndef zox_disable_rendering_instances
    zox_render3D_plus_system(VoxInstanceRenderSystem,
        [in] transforms3.TransformMatrix,
        [in] rendering.core.InstanceLink,
        [in] rendering.RenderDisabled,
        [none] rendering.core.RendererInstance)
#endif
    // upload gpu
    zox_system_1(MeshUpdateSystem, zox_pip_mainthread,
        [in] rendering.MeshDirty,
        [in] rendering.core.MeshIndicies,
        [in] rendering.core.MeshVertices,
        [in] rendering.core.MeshGPULink,
        [in] rendering.core.MaterialGPULink,
        [none] !rendering.core.MeshUVs,
        [none] !rendering.core.MeshColorRGBs)
    zox_system_1(Mesh3DTexturedUploadSystem, zox_pip_mainthread,
        [in] rendering.core.MeshIndicies,
        [in] rendering.core.MeshVertices,
        [in] rendering.core.MeshUVs,
        [in] rendering.core.MeshColorRGBs,
        [in] rendering.core.MeshGPULink,
        [in] rendering.core.UvsGPULink,
        [in] rendering.core.ColorsGPULink,
        [in] rendering.MeshDirty)
    zox_system_1(MeshUpdateCharacters3DSystem, zox_pip_mainthread,
        [in] rendering.core.MeshIndicies,
        [in] rendering.core.MeshVertices,
        [in] rendering.core.MeshColorRGBs,
        [in] rendering.MeshDirty,
        [out] rendering.core.MeshGPULink,
        [out] rendering.core.ColorsGPULink,
        [none] rendering.core.MeshColorRGBs,
        [none] !rendering.core.MeshUVs)
}