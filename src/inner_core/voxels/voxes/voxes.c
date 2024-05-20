#ifndef zox_voxes
#define zox_voxes

#define vox_model_scale (1 / 64.0f)
zox_declare_tag(Vox)
#include "data/default_palette.c"
#include "data/vox_file.c"
#include "util/vox_read_util.c"
#include "util/vox_files.c"
#include "prefabs/vox.c"
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
zox_define_tag(Vox)
zox_filter(chunks_generating, [in] GenerateChunk)
if (!headless) zox_system_ctx(ChunkOctreeColorsBuildSystem, zox_pipeline_build_voxel_mesh, chunks_generating, [out] ChunkDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] ColorRGBs, [in] ChunkSize, [in] VoxScale, [out] MeshIndicies, [out] MeshVertices, [out] MeshColorRGBs, [out] MeshDirty, [none] chunks.ColorChunk)
zox_system(Bounds3DGrowSystem, EcsPostUpdate, [in] MeshDirty, [in] ChunkSize, [in] VoxScale, [out] Bounds3D)
zoxel_end_module(Voxes)

#endif
