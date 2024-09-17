// spawning block vox entities during LOD generation step!
void BlockVoxSpawnSystem(ecs_iter_t *it) {
#if defined(zox_disable_block_voxes) || defined(zox_disable_block_voxes2)
    return;
#endif
    zox_iter_world()
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_out(ChunkOctree, chunkOctrees, 2)
    zox_field_in(ChunkPosition, chunkPositions, 3)
    zox_field_in(VoxLink, voxLinks, 4)
    zox_field_in(RenderLod, renderLods, 5)
    zox_field_in(RenderDisabled, renderDisableds, 6)
    zox_field_out(BlocksSpawned, blocksSpawneds, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value != chunk_lod_state_vox_blocks_spawn) continue;
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i(RenderLod, renderLods, renderLod)
        // zox_field_o(BlockSpawns, blockSpawnss, blockSpawns)
        zox_field_o(BlocksSpawned, blocksSpawneds, blocksSpawned)
        const unsigned char camera_distance = renderLod->value;
        const unsigned char can_have_block_voxes = camera_distance <= block_vox_render_distance;
        if (can_have_block_voxes) { //  && !blocksSpawned->value
            // lod updated here too during delve step
            const unsigned char vox_lod = get_block_voxes_lod_from_camera_distance(camera_distance);
            update_block_voxes(world, voxLink, chunkPosition, vox_lod, renderDisabled, chunkOctree); // , blockSpawns);
            blocksSpawned->value = 1;
            // zox_log("Updating Block Entities\n")
        } else if (!can_have_block_voxes && blocksSpawned->value) {
            delete_block_entities(world, chunkOctree, max_octree_depth, 0);
            blocksSpawned->value = 0;
        }
    }
} zox_declare_system(BlockVoxSpawnSystem)

// todo: destroy block voxes if removed from chunk, check hashes / current block voxes
// todo: also check if hashes exist but voxel type has changed!

// unsigned char node_index = chunkLodDirty->value - chunk_lod_state_vox_blocks_spawn;
// zox_log("node_index [%i]\n", node_index)
// update_block_voxes_on_node(world, voxLink, chunkPosition, vox_lod, renderDisabled, chunkOctree, blockSpawns, node_index);
// if (!(chunkLodDirty->value >= chunk_lod_state_vox_blocks_spawn && chunkLodDirty->value <= chunk_lod_state_vox_blocks_spawn_8)) continue;
/*if (blockSpawns->value) {
 * byte3_hashmap* hashmap = blockSpawns->value;
 * blockSpawns->value = NULL;
 * dispose_byte3_hashmap(world, hashmap);
 }
*/
