#ifndef zox_voxels
#define zox_voxels

zox_declare_tag(Chunk)
zox_declare_tag(NoiseChunk)
zox_component_int3(ChunkPosition)
zox_component_int3(VoxelPosition)
zox_component_entity(VoxLink)
zox_component_float(VoxScale)
zox_link_component(ChunkLink, ecs_entity_t, EntityLinks)
zox_hashmap_component(ChunkLinks, int3)
#include "core/voxels_core.c"
#include "structures/structures.c"
#include "terrain/terrain.c"
#include "animations/voxels_animations.c"
#include "voxes/voxes.c"

void spawn_prefabs_voxels(ecs_world_t *world) {
    spawn_prefabs_voxels_core(world);
    spawn_prefabs_voxels_structures(world);
    spawn_prefabs_terrain(world);
    spawn_prefabs_voxel_animations(world);
    spawn_prefabs_voxes(world);
}

zox_begin_module(Voxels)
zox_define_tag(Chunk)
zox_define_tag(NoiseChunk)
zox_define_component_int3(ChunkPosition)
zox_define_component_int3(VoxelPosition)
zox_define_component_entity(VoxLink)
zox_define_component_float(VoxScale)
zox_define_links_component(ChunkLink)
zox_define_hashmap_component(ChunkLinks)
zox_import_module(VoxelsCore)
zox_import_module(Structures)
zox_import_module(Terrain)
zox_import_module(VoxelsAnimations)
zox_import_module(Voxes)
zoxel_end_module(Voxels)

#endif
