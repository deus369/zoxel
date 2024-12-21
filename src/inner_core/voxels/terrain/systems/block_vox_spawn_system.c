// spawning block vox entities during LOD generation step!
const unsigned char block_vox_render_distance = 1; // 3 | 4 looks best

void BlockVoxSpawnSystem(ecs_iter_t *it) {
    if (disable_block_voxes) return;
    zox_iter_world()
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(ChunkPosition, chunkPositions, 3)
    zox_field_in(VoxLink, voxLinks, 4)
    zox_field_in(RenderDistance, renderDistances, 5)
    zox_field_in(RenderDisabled, renderDisableds, 6)
    zox_field_out(ChunkOctree, chunkOctrees, 2)
    zox_field_out(BlocksSpawned, blocksSpawneds, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value != chunk_lod_state_vox_blocks_spawn) continue;
        zox_field_i(VoxLink, voxLinks, voxLink)
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i(RenderDistance, renderDistances, renderDistance)
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_o(BlocksSpawned, blocksSpawneds, blocksSpawned)
        const unsigned char can_have_block_voxes = renderDistance->value <= block_vox_render_distance;
        if (can_have_block_voxes) {
            zox_field_e()
            const unsigned char vox_lod = get_block_voxes_lod_from_camera_distance(renderDistance->value);
            if (!blocksSpawned->value) {
                blocksSpawned->value = 1;
                update_block_voxes(world, e, voxLink->value, chunkPosition, vox_lod, renderDisabled, chunkOctree, max_octree_depth);
            } else {
                // here just update, no spawning (todo)
                // update_block_voxes(world, e, voxLink->value, chunkPosition, vox_lod, renderDisabled, chunkOctree, max_octree_depth);
            }
        } else if (!can_have_block_voxes) {
            if (blocksSpawned->value) {
                blocksSpawned->value = 0;
                delete_block_entities(world, chunkOctree, 0, max_octree_depth);
            }
        }
    }
} zox_declare_system(BlockVoxSpawnSystem)

// todo: destroy block voxes if removed from chunk, check hashes / current block voxes
// todo: also check if hashes exist but voxel type has changed!
