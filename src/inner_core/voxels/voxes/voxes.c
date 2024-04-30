#ifndef zoxel_voxes
#define zoxel_voxes

// zoxel_component_declares
zox_declare_tag(Vox)
// zoxel_data_includes
#include "data/default_palette.c"
#include "data/vox_file.c"
// zoxel_util_includes
#include "util/vox_read_util.c"
#include "util/vox_files.c"
// zoxel_prefab_includes
#include "prefabs/vox.c"
// zoxel_system_includes
#include "systems/chunk_colors_build_system.c"
#include "systems/chunk_octree_colors_build_system.c"
#include "systems/bounds3D_grow_system.c"

void dispose_voxes(ecs_world_t *world) {
    dispose_files_voxes(world);
}

void initialize_voxes(ecs_world_t *world) {
    load_files_voxes();
}

void spawn_prefabs_voxes(ecs_world_t *world) {
    spawn_prefab_vox(world);
}

zox_begin_module(Voxes)
// zoxel_component_defines
zox_define_tag(Vox)
// zoxel_filter_defines
zox_filter(chunks_generating, [in] GenerateChunk)
// zoxel_system_defines
if (!headless) zox_system_ctx(ChunkOctreeColorsBuildSystem, zox_pipeline_build_voxel_mesh, chunks_generating, [out] ChunkDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] ColorRGBs, [in] ChunkSize, [in] VoxScale, [out] MeshIndicies, [out] MeshVertices, [out] MeshColorRGBs, [out] MeshDirty, [none] voxels.core.ColorChunk)
zox_system(Bounds3DGrowSystem, EcsPostUpdate, [in] MeshDirty, [in] ChunkSize, [in] VoxScale, [out] Bounds3D)
zoxel_end_module(Voxes)

#endif
