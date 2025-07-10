#include "mesh2D_update_system.c"
#include "mesh2D_uvs_update_system.c"
#include "render2D_instance_system.c"
#include "render2D_system.c"

void define_systems_basics2D(ecs_world_t *world) {
    zox_render3D_system(RenderMaterial2DSystem,
        [in] transforms2.d.Position2D,
        [in] transforms2.d.Rotation2D,
        [in] transforms.Scale1D,
        [in] rendering.Brightness,
        [in] rendering.core.MaterialGPULink,
        [in] rendering.core.TextureGPULink,
        [none] !rendering.core.MeshGPULink)
    zox_system_1(Mesh2DUpdateSystem, zox_pip_mainthread,
        [out] rendering.MeshDirty,
        [in] rendering.core.MeshIndicies,
        [in] rendering.core.MeshVertices2D,
        [in] rendering.core.MeshGPULink,
        [in] rendering.core.MaterialGPULink,
        [none] !rendering.core.MeshUVs,
        [none] !rendering.core.MeshColorRGBs)
    zox_system_1(Mesh2DUvsUpdateSystem, zox_pip_mainthread,
        [in] rendering.core.MeshIndicies,
        [in] rendering.core.MeshVertices2D,
        [in] rendering.core.MeshUVs,
        [in] rendering.core.MeshGPULink,
        [in] rendering.core.UvsGPULink,
        [out] rendering.MeshDirty)
}