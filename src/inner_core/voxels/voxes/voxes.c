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
#include "util/vox_read_util.c"
#include "util/vox_util.c"
#include "prefabs/prefabs.c"
#include "util/vox_files.c"
#include "util/io_util.c"
#include "systems/chunk_colors_build_system.c"
#include "systems/chunk_octree_colors_build_system.c"
#include "systems/bounds3D_grow_system.c"
#include "systems/generate_vox_system.c"
#include "systems/vox_texture_system.c"

zox_begin_module(Voxes)
zox_define_tag(Vox)
zox_define_tag(BlendVox)
zox_define_tag(VoxRubble)
zox_define_component_byte(GenerateVox)
zox_filter(chunks_generating, [in] GenerateChunk)
// Builds our Colored Chunks (Voxes)
if (!headless) zox_system_ctx(ChunkOctreeColorsBuildSystem, zox_pip_voxels_chunk_clean, chunks_generating, [out] ChunkDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] ColorRGBs, [in] ChunkSize, [in] VoxScale, [in] RenderDisabled, [out] MeshIndicies, [out] MeshVertices, [out] MeshColorRGBs, [out] MeshDirty, [none] chunks.ColorChunk)
zox_system(Bounds3DGrowSystem, zox_pip_voxels_chunk_clean, [in] MeshDirty, [in] ChunkSize, [in] VoxScale, [out] Bounds3D) // remember: timing specific, fucks up if changes position
zox_system(GenerateVoxSystem, zox_pip_voxels, [in] Color, [out] GenerateVox, [out] ChunkOctree, [out] ColorRGBs, [out] ChunkDirty)
zox_system(VoxTextureSystem, zox_pip_voxels_chunk_dirty, [in] TextureSize, [in] VoxLink, [in] VoxBakeSide, [out] GenerateTexture, [out] TextureData, [out] TextureDirty, [none] textures.core.VoxTexture)
initialize_voxes(world);
spawn_prefabs_voxes(world);
zoxel_end_module(Voxes)

#endif
