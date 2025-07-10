#include "chunk_colors_build_system.c"
#include "bounds3D_grow_system.c"
#include "generate_vox_system.c"
#include "vox_texture_system.c"
#include "clone_vox_system.c"

void define_systems_voxes(ecs_world_t *world) {
    zox_system(VoxTextureSystem, EcsPreUpdate,
        [in] textures.core.TextureSize,
        [in] voxels.VoxLink,
        [in] blocks.VoxBakeSide,
        [out] textures.core.GenerateTexture,
        [out] textures.core.TextureData,
        [out] rendering.TextureDirty,
        [none] textures.core.VoxTexture)
    // remember: timing specific, fucks up if changes position
    zox_system(Bounds3DGrowSystem, EcsOnUpdate,
        [in] rendering.MeshDirty,
        [in] chunks.ChunkSize,
        [in] blocks.VoxScale,
        [out] generic.Bounds3D)
    zox_system(GenerateVoxSystem, EcsOnUpdate,
        [in] colorz.Color,
        [out] GenerateVox,
        [out] chunks.VoxelNode,
        [out] chunks.NodeDepth,
        [out] colorz.ColorRGBs,
        [out] chunks.ChunkMeshDirty)
    zox_system(CloneVoxSystem, EcsOnUpdate,
        [in] CloneVoxLink,
        [out] CloneVox,
        [out] chunks.VoxelNode,
        [out] chunks.NodeDepth,
        [out] chunks.ChunkSize,
        [out] colorz.ColorRGBs,
        [out] chunks.ChunkMeshDirty,
        [out] ChunkLod)
    if (!headless) {
        zox_system(ChunkColorsBuildSystem, EcsOnUpdate,
            [in] chunks.ChunkMeshDirty,
            [in] chunks.VoxelNode,
            [in] chunks.NodeDepth,
            [in] rendering.RenderLod,
            [in] chunks.ChunkNeighbors,
            [in] colorz.ColorRGBs,
            [in] chunks.ChunkSize,
            [in] blocks.VoxScale,
            [out] rendering.core.MeshIndicies,
            [out] rendering.core.MeshVertices,
            [out] rendering.core.MeshColorRGBs,
            [out] rendering.MeshDirty,
            [none] chunks.ColorChunk)
    }
}