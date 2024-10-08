#ifndef zox_voxes
#define zox_voxes

#include "data/default_palette.c"
#include "data/vox_file.c"
#include "data/spawn_block_vox.c"
#include "data/settings.c"
zox_declare_tag(Vox)
zox_declare_tag(BlendVox)
zox_declare_tag(VoxRubble)
zox_component_byte(GenerateVox)
zox_component_byte(CloneVox)
zox_component_byte(ChunkLod)
zox_component_entity(CloneVoxLink)
#include "util/vox_read_util.c"
#include "util/vox_util.c"
#include "util/generate_util.c"
#include "prefabs/prefabs.c"
#include "util/vox_files.c"
#include "util/io_util.c"
#include "util/voronoi3D.c"
#include "systems/chunk_colors_build_system.c"
#include "systems/chunk_octree_colors_build_system.c"
#include "systems/bounds3D_grow_system.c"
#include "systems/generate_vox_system.c"
#include "systems/vox_texture_system.c"
#include "systems/clone_vox_system.c"

void dispose_voxes(ecs_world_t *world, void *ctx) {
    dispose_files_voxes(world);
}
zox_begin_module(Voxes)
zox_module_dispose(dispose_voxes)
zox_define_tag(Vox)
zox_define_tag(BlendVox)
zox_define_tag(VoxRubble)
zox_define_component_byte(GenerateVox)
zox_define_component_byte(ChunkLod)
zox_define_component_byte(CloneVox)
zox_define_component_entity(CloneVoxLink)
// zox_filter(chunks_generating, [in] GenerateChunk)
// Builds our Colored Chunks (Voxes)
// _ctx chunks_generating, zox_pip_voxels_chunk_clean
if (!headless) zox_system(ChunkOctreeColorsBuildSystem, zox_pip_voxels, [out] ChunkDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] ColorRGBs, [in] ChunkSize, [in] VoxScale, [in] RenderDisabled, [out] MeshIndicies, [out] MeshVertices, [out] MeshColorRGBs, [out] MeshDirty, [none] chunks.ColorChunk)
// zox_pip_voxels_chunk_clean
zox_system(Bounds3DGrowSystem, zox_pip_voxels, [in] MeshDirty, [in] ChunkSize, [in] VoxScale, [out] Bounds3D) // remember: timing specific, fucks up if changes position
zox_system(GenerateVoxSystem, zox_pip_voxels, [in] Color, [out] GenerateVox, [out] ChunkOctree, [out] ColorRGBs, [out] ChunkDirty)
zox_system(VoxTextureSystem, zox_pip_voxels_chunk_dirty, [in] TextureSize, [in] VoxLink, [in] VoxBakeSide, [out] GenerateTexture, [out] TextureData, [out] TextureDirty, [none] textures.core.VoxTexture)
zox_system(CloneVoxSystem, zox_pip_voxels, [in] CloneVoxLink, [out] CloneVox, [out] ChunkOctree, [out] ChunkSize, [out] ColorRGBs, [out] ChunkDirty, [out] ChunkLod)
initialize_voxes(world);
spawn_prefabs_voxes(world);
zoxel_end_module(Voxes)

#endif
