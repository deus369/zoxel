// spawning block vox entities during LOD generation step!
// todo: move this to a render distance dirty step!
void BlockVoxSpawnSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_sys_begin()
    zox_sys_in(ChunkLodDirty)
    zox_sys_in(ChunkPosition)
    zox_sys_in(VoxLink)
    zox_sys_in(NodeDepth)
    zox_sys_in(RenderDistance)
    zox_sys_in(RenderDisabled)
    zox_sys_in(RenderLod)
    zox_sys_out(VoxelNode)
    zox_sys_out(BlocksSpawned)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(ChunkLodDirty, chunkLodDirty)
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(ChunkPosition, chunkPosition)
        zox_sys_i(RenderDistance, renderDistance)
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_o(VoxelNode, voxelNode)
        zox_sys_o(BlocksSpawned, blocksSpawned)
        if (chunkLodDirty->value != chunk_lod_state_vox_blocks_spawn) {
            continue;
        }
        const byte can_have_block_voxes = renderLod->value <= block_vox_render_at_lod;
        if (can_have_block_voxes) {
            const byte vox_lod = get_block_voxes_lod_from_camera_distance(renderDistance->value);
            if (!blocksSpawned->value) {
                blocksSpawned->value = 1;
                update_block_voxes(world, e, voxLink->value, chunkPosition, vox_lod, renderDisabled, voxelNode, nodeDepth->value);
            }
        } else if (!can_have_block_voxes) {
            if (blocksSpawned->value) {
                blocksSpawned->value = 0;
                delete_block_entities(world, voxelNode); //, 0, nodeDepth->value);
            }
        }
    }
} zox_declare_system(BlockVoxSpawnSystem)