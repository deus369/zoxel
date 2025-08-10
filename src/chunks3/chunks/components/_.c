zox_tag(Chunk);
zox_tag(NoiseChunk);
zox_tag(ChunkDebugger);
zox_tag(ColorChunk);
zox_tag(ChunkTextured);
zox_tag(LinkChunk);
zox_tag(DisableReverseLinkChunk);
zoxc_byte(ChunkDirty);
zoxc_byte(ChunkMeshDirty);
zoxc_byte(ChunkLodDirty);
zoxc_byte(GenerateChunk);
zoxc_int3(ChunkPosition);
zoxc_int3(ChunkSize);
zoxc_byte(BlocksSpawned);
zoxc_byte(NodeDepth);
zoxc_byte(VoxelNodeDirty);
zoxc_byte(VoxelNodeEdited);
zoxc_byte(VoxelNodeLoaded);
zoxc_float(RaycastRange);
#include "neighbors.c"
#include "chunk_links.c"

zoxc_link(ChunkLink, entity, ChunkEntities)
zoxc_node(VoxelNode, byte, 0)
zox_node_add_link(VoxelNode)
zoxc_node_helper(VoxelNode, byte)

void define_components_chunks(ecs *world) {
    zox_define_tag(Chunk);
    zox_define_tag(NoiseChunk);
    zox_define_tag(ColorChunk);
    zox_define_tag(ChunkTextured);
    zox_define_tag(LinkChunk);
    zox_define_tag(DisableReverseLinkChunk);
    zox_define_tag(ChunkDebugger);
    zox_define_component_int3(ChunkPosition);
    zoxd_byte(ChunkDirty);
    zoxd_byte(ChunkMeshDirty);
    zoxd_byte(ChunkLodDirty);
    zox_define_component_int3(ChunkSize);
    zoxd_byte(GenerateChunk);
    zoxd_byte(BlocksSpawned);
    zox_define_component(ChunkNeighbors);
    zox_define_links_component(ChunkLink);
    zoxd_byte(NodeDepth);
    zox_define_component_node(VoxelNode);
    zoxd_byte(VoxelNodeDirty);
    zoxd_byte(VoxelNodeEdited);
    zoxd_byte(VoxelNodeLoaded);
    zox_define_hashmap_component(ChunkLinks);
}