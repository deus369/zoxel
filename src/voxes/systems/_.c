#include "chunk_colors_build_system.c"
#include "bounds3D_grow_system.c"
#include "vox_generation_system.c"
#include "vox_texture_system.c"
#include "clone_vox_system.c"

void define_systems_voxes(ecs_world_t *world) {
    zox_system(VoxTextureSystem, EcsPreUpdate,
        [in] rendering.TextureSize,
        [in] chunks3.VoxLink,
        [in] blocks.VoxBakeSide,
        [out] textures.GenerateTexture,
        [out] textures.TextureData,
        [out] rendering.TextureDirty,
        [none] textures.VoxTexture)
    // remember: timing specific, fucks up if changes position
    zox_system(Bounds3DGrowSystem, EcsOnUpdate,
        [in] rendering.MeshDirty,
        [in] chunks3.ChunkSize,
        [in] blocks.VoxScale,
        [out] generic.Bounds3D)
    zox_system(VoxGenerationSystem, EcsOnUpdate,
        [in] colorz.Color,
        [in] VoxType,
        [out] GenerateVox,
        [out] chunks3.VoxelNode,
        [out] chunks3.NodeDepth,
        [out] colorz.ColorRGBs,
        [out] chunks3.ChunkMeshDirty)
    zox_system(CloneVoxSystem, EcsOnUpdate,
        [in] CloneVoxLink,
        [out] CloneVox,
        [out] chunks3.VoxelNode,
        [out] chunks3.NodeDepth,
        [out] chunks3.ChunkSize,
        [out] colorz.ColorRGBs,
        [out] chunks3.ChunkMeshDirty,
        [out] ChunkLod)
    if (!headless) {
        zox_system(ChunkColorsBuildSystem, EcsOnUpdate,
            [in] chunks3.ChunkMeshDirty,
            [in] chunks3.VoxelNode,
            [in] chunks3.NodeDepth,
            [in] rendering.RenderLod,
            [in] chunks3.ChunkNeighbors,
            [in] colorz.ColorRGBs,
            [in] chunks3.ChunkSize,
            [in] blocks.VoxScale,
            [out] rendering.MeshIndicies,
            [out] rendering.MeshVertices,
            [out] rendering.MeshColorRGBs,
            [out] rendering.MeshDirty,
            [none] chunks3.ColorChunk)
    }
}