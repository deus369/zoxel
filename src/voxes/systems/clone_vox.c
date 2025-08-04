// todo: make use TargetChunkLod -> and load/unload depth based on that
// todo: set lod here instead of just applying RenderLod only with ChunkMeshDirty -> keeps memory down
void CloneVoxSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(CloneVoxLink)
    zox_sys_out(CloneVox)
    zox_sys_out(VoxelNode)
    zox_sys_out(NodeDepth)
    zox_sys_out(ChunkSize)
    zox_sys_out(ColorRGBs)
    zox_sys_out(ChunkMeshDirty)
    zox_sys_out(ChunkLod)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(CloneVoxLink, cloneVoxLink)
        zox_sys_o(VoxelNode, voxelNode)
        zox_sys_o(NodeDepth, nodeDepth)
        zox_sys_o(ColorRGBs, colorRGBs)
        zox_sys_o(ChunkSize, chunkSize)
        zox_sys_o(ChunkMeshDirty, chunkMeshDirty)
        zox_sys_o(ChunkLod, chunkLod)
        zox_sys_o(CloneVox, cloneVox)
        const ecs_entity_t src = cloneVoxLink->value;
        if (!cloneVox->value || !src) {
            continue;
        }
        if (!zox_has(src, VoxelNode)) {
            continue;
        }
        // clone one depth at a time
        zox_geter(src, VoxelNode, source_node)
        zox_geter(src, NodeDepth, source_node_depth)
        zox_geter(src, ChunkSize, source_chunk_size)
        zox_geter(src, ColorRGBs, colors_source)
        if (chunkLod->value == 255) {
            chunkLod->value = 0;
        } else {
            chunkLod->value++;
        }
        nodeDepth->value = source_node_depth->value;
        clone_at_depth_VoxelNode(voxelNode, source_node, chunkLod->value, 0);
        const byte target_depth = nodeDepth->value;
        if (chunkLod->value == target_depth) {
            const int memory_length = sizeof(color_rgb) * colors_source->length;
            chunkSize->value = source_chunk_size->value;
            colorRGBs->length = colors_source->length;

            initialize_ColorRGBs(colorRGBs, memory_length);
            memcpy(colorRGBs->value, colors_source->value, memory_length);
            cloneVox->value = 0;
            chunkMeshDirty->value = chunk_dirty_state_trigger;
        }
    }
} zox_declare_system(CloneVoxSystem)