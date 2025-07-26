#include "skeleton_render3D_system.c"
#include "bone_index_generate_system.c"
#include "bone_index_upload_system.c"
#include "bone_paint_system.c"

void define_systems_bones(ecs_world_t *world) {
    // generating bone indexes here
    if (!headless) {
        zox_render3D_plus_system(Skeleton3RenderSystem,
            [in] rendering.MeshIndicies,
            [in] rendering.MeshGPULink,
            [in] rendering.ColorsGPULink,
            [in] BoneIndexGPULink,
            [in] transforms3.TransformMatrix,
            [in] rendering.RenderDisabled,
            [in] BoneLinks,
            [none] rendering3.SkeletonMesh,
            [none] rendering.MeshColorRGBs,
            [none] !rendering.UvsGPULink)
        zox_system(BoneIndexGenerateSystem, EcsOnUpdate,
            [in] rendering.MeshDirty,
            [in] rendering.MeshVertices,
            [in] BoneLinks,
            [out] BoneIndexes)
        zox_system(BonePaintSystem, EcsPostUpdate,
            [in] rendering.MeshDirty,
            [in] BoneIndexes,
            [out] rendering.MeshColorRGBs,
            [none] PaintedSkeleton)
        zox_system_1(BoneIndexUploadSystem, zox_pip_mainthread,
            [in] rendering.MeshDirty,
            [in] BoneIndexes,
            [out] BoneIndexGPULink)
    }
}