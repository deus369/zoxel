#include "mesh2D_update_system.c"
#include "mesh2D_uvs_update_system.c"
#include "render2D_instance_system.c"
#include "render2D_system.c"

void define_systems_basics2D(ecs_world_t *world) {
    zox_render3D_system(RenderMaterial2DSystem,
        [in] transforms2.Position2D,
        [in] transforms2.Rotation2D,
        [in] transforms.Scale1D,
        [in] rendering.Brightness,
        [in] rendering.MaterialGPULink,
        [in] rendering.TextureGPULink,
        [none] !rendering.MeshGPULink)
    zox_system_1(Mesh2DUpdateSystem, zox_pip_mainthread,
        [out] rendering.MeshDirty,
        [in] rendering.MeshIndicies,
        [in] rendering.MeshVertices2D,
        [in] rendering.MeshGPULink,
        [in] rendering.MaterialGPULink,
        [none] !rendering.MeshUVs,
        [none] !rendering.MeshColorRGBs)
    zox_system_1(Mesh2DUvsUpdateSystem, zox_pip_mainthread,
        [in] rendering.MeshIndicies,
        [in] rendering.MeshVertices2D,
        [in] rendering.MeshUVs,
        [in] rendering.MeshGPULink,
        [in] rendering.UvsGPULink,
        [out] rendering.MeshDirty)
}