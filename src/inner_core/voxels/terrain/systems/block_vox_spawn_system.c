// spawning block vox entities during generation step!
void BlockVoxSpawnSystem(ecs_iter_t *it) {
#ifdef zox_disable_block_voxes
    return;
#endif
    zox_iter_world()
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(ChunkOctree, chunkOctrees, 2)
    zox_field_in(ChunkPosition, chunkPositions, 3)
    zox_field_in(VoxLink, voxLinks, 4)
    zox_field_in(RenderLod, renderLods, 5)
    zox_field_in(RenderDisabled, renderDisableds, 6)
    zox_field_out(BlockSpawns, blockSpawnss, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value != 3) continue;
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_i(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i(RenderLod, renderLods, renderLod)
        zox_field_o(BlockSpawns, blockSpawnss, blockSpawns)
        const unsigned char camera_distance = renderLod->value;
        const unsigned char can_have_block_voxes = camera_distance <= block_vox_render_distance;
        if (can_have_block_voxes) {
            update_block_voxes(world, voxLink, chunkPosition, renderLod, renderDisabled, chunkOctree, blockSpawns);
        } else {
            if (blockSpawns->value) {
                byte3_hashmap* hashmap = blockSpawns->value;
                blockSpawns->value = NULL;
                dispose_byte3_hashmap(world, hashmap);
            }
        }
    }
} zox_declare_system(BlockVoxSpawnSystem)

// todo: destroy block voxes if removed from chunk, check hashes / current block voxes
// todo: also check if hashes exist but voxel type has changed!
