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

void define_systems_basics3D(ecs *world) {
    // skybox
    zox_render3D_plus_system(Render3DSystem,
        [in] transforms3.TransformMatrix,
        [in] rendering.Brightness,
        [in] rendering.MeshGPULink,
        [in] rendering.MeshIndicies,
        [in] rendering.MaterialGPULink,
        [none] MeshBasic3D)
    // unique textured meshes - items
    zox_render3D_plus_system(TexturedRenderSystem,
        [in] transforms3.TransformMatrix,
        [in] rendering.MeshGPULink,
        [in] rendering.UvsGPULink,
        [in] rendering.ColorsGPULink,
        [in] rendering.MeshIndicies,
        [in] rendering.RenderDisabled,
        [in] rendering.MaterialGPULink,
        [in] rendering.TextureGPULink,
        [in] MaterialTextured3D,
        [none] TexturedMesh3D)
    // characters
    zox_render3D_plus_system(Characters3RenderSystem,
        [in] rendering.MeshIndicies,
        [in] rendering.MeshGPULink,
        [in] rendering.ColorsGPULink,
        [in] transforms3.TransformMatrix,
        [in] rendering.RenderDisabled,
        [none] rendering.MeshColorRGBs,
        [none] !rendering.UvsGPULink,
        [none] rendering.VoxMesh,
        [none] !rendering3.SkeletonMesh)
#ifndef zox_disable_rendering_instances
    zox_render3D_plus_system(VoxInstanceRenderSystem,
        [in] transforms3.TransformMatrix,
        [in] rendering.InstanceLink,
        [in] rendering.RenderDisabled,
        [none] rendering.RendererInstance)
#endif
    // upload gpu
    zox_system_1(MeshUpdateSystem, zoxp_mainthread,
        [in] rendering.MeshDirty,
        [in] rendering.MeshIndicies,
        [in] rendering.MeshVertices,
        [in] rendering.MeshGPULink,
        [in] rendering.MaterialGPULink,
        [none] !rendering.MeshUVs,
        [none] !rendering.MeshColorRGBs)
    zox_system_1(Mesh3DTexturedUploadSystem, zoxp_mainthread,
        [in] rendering.MeshIndicies,
        [in] rendering.MeshVertices,
        [in] rendering.MeshUVs,
        [in] rendering.MeshColorRGBs,
        [in] rendering.MeshGPULink,
        [in] rendering.UvsGPULink,
        [in] rendering.ColorsGPULink,
        [in] rendering.MeshDirty)
    zox_system_1(MeshUpdateCharacters3DSystem, zoxp_mainthread,
        [in] rendering.MeshIndicies,
        [in] rendering.MeshVertices,
        [in] rendering.MeshColorRGBs,
        [in] rendering.MeshDirty,
        [out] rendering.MeshGPULink,
        [out] rendering.ColorsGPULink,
        [none] rendering.MeshColorRGBs,
        [none] !rendering.MeshUVs)
}