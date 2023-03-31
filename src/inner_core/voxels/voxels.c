#ifndef zoxel_voxels
#define zoxel_voxels

bool disable_chunk_systems;
ecs_entity_t main_terrain_world;
zoxel_declare_tag(Chunk)
zoxel_declare_tag(NoiseChunk)
zoxel_component(ChunkPosition, int3)
zoxel_component(VoxelPosition, int3)
zoxel_component(VoxLink, ecs_entity_t)
zoxel_component(ChunkLink, ecs_entity_t)
// zoxel_memory_component(ChunkLinks, ecs_entity_t)
zoxel_component(ChunkLinks, int3_hash_map*)
#include "core/core_voxels.c"
#include "terrain/terrain.c"
#include "vox/vox.c"

ECS_DTOR(ChunkLinks, ptr, {
    if (ptr->value != NULL) {
        int3_hash_map_dispose(ptr->value);
    }
})

zoxel_begin_module(Voxels)
zoxel_define_tag(Chunk)
zoxel_define_tag(NoiseChunk)
zoxel_define_component(ChunkPosition)
zoxel_define_component(VoxelPosition)
zoxel_define_component(VoxLink)
zoxel_define_component(ChunkLink)
zoxel_define_component(ChunkLinks)
ecs_set_hooks(world, ChunkLinks, { .dtor = ecs_dtor(ChunkLinks) });
// zoxel_define_memory_component(ChunkLinks)
zoxel_import_module(VoxelsCore)
zoxel_import_module(Vox)
zoxel_import_module(Terrain)
zoxel_end_module(Voxels)

#endif