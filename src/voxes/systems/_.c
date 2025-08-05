#include "build_chunk.c"
#include "grow_bounds3.c"
#include "vox_generation.c"
#include "vox_texture.c"
#include "clone_vox.c"
#include "bake_vox.c"
zox_increment_system_with_reset(GenerateVox, zox_dirty_end);

void define_systems_voxes(ecs_world_t *world) {
    zox_define_increment_system(GenerateVox);
    // remember: timing specific, fucks up if changes position
    zox_system(Bounds3GrowSystem, EcsOnUpdate,
            [in] rendering.MeshDirty,
            [in] chunks3.ChunkSize,
            [in] blocks.VoxScale,
            [out] generic.Bounds3D)
    zox_system(VoxTextureSystem, EcsPreUpdate,
            [in] rendering.TextureSize,
            [in] chunks3.VoxLink,
            [in] blocks.VoxBakeSide,
            [out] texturez.GenerateTexture,
            [out] texturez.TextureData,
            [out] rendering.TextureDirty,
            [none] texturez.VoxTexture)
    // NOTE: Writes to VoxelNode
    zox_system(VoxGenerationSystem, zoxp_write_voxels,
            [in] GenerateVox,
            [in] colorz.Color,
            [in] VoxType,
            [out] chunks3.VoxelNode,
            [out] chunks3.VoxelNodeDirty,
            [out] chunks3.NodeDepth,
            [out] colorz.ColorRGBs)
    // NOTE: Writes to VoxelNode
    zox_system(CloneVoxSystem, zoxp_write_voxels,
            [in] CloneVoxLink,
            [out] CloneVox,
            [out] chunks3.VoxelNode,
            [out] chunks3.NodeDepth,
            [out] chunks3.ChunkSize,
            [out] colorz.ColorRGBs,
            [out] chunks3.VoxelNodeDirty,
            [out] ChunkLod)
    zox_system(BakeVoxSystem, EcsOnUpdate,
            [in] rendering.ModelLink,
            [in] texturez.TextureLinks)
    if (!headless) {
        zox_system(ChunkColorsBuildSystem, zoxp_read_voxels,
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