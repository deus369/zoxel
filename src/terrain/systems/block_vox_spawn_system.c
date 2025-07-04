// spawning block vox entities during LOD generation step!

void BlockVoxSpawnSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(ChunkPosition, chunkPositions, 3)
    zox_field_in(VoxLink, voxLinks, 4)
    zox_field_in(RenderDistance, renderDistances, 5)
    zox_field_in(RenderDisabled, renderDisableds, 6)
    zox_field_in(RenderLod, renderLods, 8)
    zox_field_out(ChunkOctree, chunkOctrees, 2)
    zox_field_out(BlocksSpawned, blocksSpawneds, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value != chunk_lod_state_vox_blocks_spawn) {
            continue;
        }
        zox_field_i(VoxLink, voxLinks, voxLink)
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i(RenderDistance, renderDistances, renderDistance)
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        zox_field_i(RenderLod, renderLods, renderLod)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_o(BlocksSpawned, blocksSpawneds, blocksSpawned)
        const byte can_have_block_voxes = renderLod->value <= block_vox_render_at_lod;
        // renderDistance->value <= block_vox_render_distance;
        if (can_have_block_voxes) {
            zox_field_e()
            const byte vox_lod = get_block_voxes_lod_from_camera_distance(renderDistance->value);
            if (!blocksSpawned->value) {
                blocksSpawned->value = 1;
                update_block_voxes(world, e, voxLink->value, chunkPosition, vox_lod, renderDisabled, chunkOctree, chunkOctree->linked);
            }
        } else if (!can_have_block_voxes) {
            if (blocksSpawned->value) {
                blocksSpawned->value = 0;
                delete_block_entities(world, chunkOctree, 0, chunkOctree->linked);
            }
        }
    }
} zox_declare_system(BlockVoxSpawnSystem)