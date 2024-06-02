void BlockVoxUpdateSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ChunkDirty, chunkDirtys, 1)
    zox_field_in(ChunkOctree, chunkOctrees, 2)
    zox_field_in(ChunkPosition, chunkPositions, 3)
    zox_field_in(VoxLink, voxLinks, 4)
    zox_field_in(RenderLod, renderLods, 5)
    zox_field_in(RenderDisabled, renderDisableds, 6)
    zox_field_out(BlockSpawns, blockSpawnss, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkDirty, chunkDirtys, chunkDirty)
        if (!chunkDirty->value) continue;
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
            // zox_log(" > updating %lu block voxes [%i]\n", it->entities[i], chunkDirty->value)
            update_block_voxes(world, voxLink, chunkPosition, renderLod, renderDisabled, chunkOctree, blockSpawns);
        }
    }
} zox_declare_system(BlockVoxUpdateSystem)
