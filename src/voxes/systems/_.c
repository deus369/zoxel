#include "chunk_octree_colors_build_system.c"
#include "bounds3D_grow_system.c"
#include "generate_vox_system.c"
#include "vox_texture_system.c"
#include "clone_vox_system.c"

void define_systems_voxes(ecs_world_t *world) {
    zox_system(VoxTextureSystem, EcsPreUpdate, [in] TextureSize, [in] VoxLink, [in] VoxBakeSide, [out] GenerateTexture, [out] TextureData, [out] TextureDirty, [none] textures.core.VoxTexture)
    zox_system(Bounds3DGrowSystem, EcsOnUpdate, [in] MeshDirty, [in] ChunkSize, [in] VoxScale, [out] Bounds3D) // remember: timing specific, fucks up if changes position
    zox_system(GenerateVoxSystem, EcsOnUpdate, [in] Color, [out] GenerateVox, [out] ChunkOctree, [out] ColorRGBs, [out] ChunkMeshDirty)
    zox_system(CloneVoxSystem, EcsOnUpdate, [in] CloneVoxLink, [out] CloneVox, [out] ChunkOctree, [out] ChunkSize, [out] ColorRGBs, [out] ChunkMeshDirty, [out] ChunkLod)
    if (!headless) {
        zox_system(ChunkOctreeColorsBuildSystem, EcsOnUpdate, [in] ChunkMeshDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] ColorRGBs, [in] ChunkSize, [in] VoxScale, [in] RenderDisabled, [out] MeshIndicies, [out] MeshVertices, [out] MeshColorRGBs, [out] MeshDirty, [none] chunks.ColorChunk)
    }
}