// spawning block vox entities during LOD generation step!

void BlockVoxSpawnSystem(ecs_iter_t *it) {
    zox_field_world()
    byte fi = 1;
    zox_field_in(ChunkLodDirty, chunkLodDirtys, fi++)
    zox_field_in(ChunkPosition, chunkPositions, fi++)
    zox_field_in(VoxLink, voxLinks, fi++)
    zox_field_in(NodeDepth, nodeDepths, fi++)
    zox_field_in(RenderDistance, renderDistances, fi++)
    zox_field_in(RenderDisabled, renderDisableds, fi++)
    zox_field_in(RenderLod, renderLods, fi++)
    zox_field_out(ChunkOctree, chunkOctrees, fi++)
    zox_field_out(BlocksSpawned, blocksSpawneds, fi++)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        zox_field_i(VoxLink, voxLinks, voxLink)
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i(RenderDistance, renderDistances, renderDistance)
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        zox_field_i(RenderLod, renderLods, renderLod)
        zox_field_i(NodeDepth, nodeDepths, nodeDepth)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_o(BlocksSpawned, blocksSpawneds, blocksSpawned)
        if (chunkLodDirty->value != chunk_lod_state_vox_blocks_spawn) {
            continue;
        }
        const byte can_have_block_voxes = renderLod->value <= block_vox_render_at_lod;
        // renderDistance->value <= block_vox_render_distance;
        if (can_have_block_voxes) {
            zox_field_e()
            const byte vox_lod = get_block_voxes_lod_from_camera_distance(renderDistance->value);
            if (!blocksSpawned->value) {
                blocksSpawned->value = 1;
                update_block_voxes(world, e, voxLink->value, chunkPosition, vox_lod, renderDisabled, chunkOctree, nodeDepth->value);
            }
        } else if (!can_have_block_voxes) {
            if (blocksSpawned->value) {
                blocksSpawned->value = 0;
                delete_block_entities(world, chunkOctree, 0, nodeDepth->value);
            }
        }
    }
} zox_declare_system(BlockVoxSpawnSystem)