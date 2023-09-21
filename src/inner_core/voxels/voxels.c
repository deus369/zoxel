#ifndef zoxel_voxels
#define zoxel_voxels

#define model_scale (1 / 64.0f) // 0.0006f         // 0.015f
// zoxel_component_includes
zox_declare_tag(Chunk)
zox_declare_tag(NoiseChunk)
zox_component(ChunkPosition, int3)
zox_component(VoxelPosition, int3)
zox_component(VoxLink, ecs_entity_t)
zox_component(ChunkLink, ecs_entity_t)
zox_hashmap_component(ChunkLinks, int3)
// zoxel_module_includes
#include "core/voxels_core.c"
#include "terrain/terrain.c"
#include "animations/voxels_animations.c"
#include "voxes/voxes.c"

void spawn_prefabs_voxels(ecs_world_t *world) {
    spawn_prefabs_voxels_core(world);
    spawn_prefabs_terrain(world);
    spawn_prefabs_voxel_animations(world);
    spawn_prefabs_voxes(world);
}

zox_begin_module(Voxels)
// zoxel_component_defines
zox_define_tag(Chunk)
zox_define_tag(NoiseChunk)
zox_define_component(ChunkPosition)
zox_define_component(VoxelPosition)
zox_define_component(VoxLink)
zox_define_component(ChunkLink)
zox_define_hashmap_component(ChunkLinks, [in] ChunkLinks)
// zoxel_module_defines
zox_import_module(VoxelsCore)
zox_import_module(Terrain)
zox_import_module(VoxelsAnimations)
zox_import_module(Vox)
zoxel_end_module(Voxels)

#endif