zox_declare_tag(Chunk)
zox_declare_tag(NoiseChunk)
zox_declare_tag(ChunkDebugger)
zox_declare_tag(ColorChunk)
zox_declare_tag(ChunkTextured)
zox_declare_tag(LinkChunk)
zox_declare_tag(DisableReverseLinkChunk)
zox_component_byte(ChunkDirty)
zox_component_byte(ChunkMeshDirty)
zox_component_byte(ChunkLodDirty)
zox_component_byte(GenerateChunk)
zox_component_int3(ChunkPosition)
zox_component_int3(ChunkSize)
zox_component_byte(OctreeDepth)
zox_component_byte(BlocksSpawned)
zox_link_component(ChunkLink, ecs_entity_t, EntityLinks)
#include "neighbors.c"
// dynamic
#include "octree_component.c"
zoxel_octree_component(ChunkOctree, byte, 0)
#include "chunk_links.c"
// more
#include "raycast_voxel_data.c"

void define_components_chunks(ecs_world_t *world) {
    zox_define_tag(Chunk)
    zox_define_tag(NoiseChunk)
    zox_define_tag(ColorChunk)
    zox_define_tag(ChunkTextured)
    zox_define_tag(LinkChunk)
    zox_define_tag(DisableReverseLinkChunk)
    zox_define_tag(ChunkDebugger)
    zox_define_component_int3(ChunkPosition)
    zox_define_component_byte(ChunkDirty)
    zox_define_component_byte(ChunkMeshDirty)
    zox_define_component_byte(ChunkLodDirty)
    zox_define_component_int3(ChunkSize)
    zox_define_component_byte(GenerateChunk)
    zox_define_component_byte(OctreeDepth)
    zox_define_component_byte(BlocksSpawned)
    zox_define_component(RaycastVoxelData)
    zox_define_component(ChunkNeighbors)
    zox_define_links_component(ChunkLink)
    // dynamic
    zox_define_component_octree(ChunkOctree)
    zox_define_hashmap_component(ChunkLinks)
}