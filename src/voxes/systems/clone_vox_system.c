// todo: make use TargetChunkLod -> and load/unload depth based on that
// todo: set lod here instead of just applying RenderLod only with ChunkMeshDirty -> keeps memory down

void CloneVoxSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(CloneVoxLink, cloneVoxLinks, 1)
    zox_field_out(CloneVox, cloneVoxes, 2)
    zox_field_out(ChunkOctree, chunkOctrees, 3)
    zox_field_out(NodeDepth, nodeDepths, 4)
    zox_field_out(ChunkSize, chunkSizes, 5)
    zox_field_out(ColorRGBs, colorRGBss, 6)
    zox_field_out(ChunkMeshDirty, chunkMeshDirtys, 7)
    zox_field_out(ChunkLod, chunkLods, 8)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(CloneVox, cloneVoxes, cloneVox)
        zox_field_i(CloneVoxLink, cloneVoxLinks, cloneVoxLink)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_o(NodeDepth, nodeDepths, nodeDepth)
        zox_field_o(ColorRGBs, colorRGBss, colorRGBs)
        zox_field_o(ChunkSize, chunkSizes, chunkSize)
        zox_field_o(ChunkMeshDirty, chunkMeshDirtys, chunkMeshDirty)
        zox_field_o(ChunkLod, chunkLods, chunkLod)
        if (!cloneVox->value || !cloneVoxLink->value) {
            continue;
        }
        const ecs_entity_t source = cloneVoxLink->value;
        // clone one depth at a time
        zox_geter(source, ChunkOctree, chunk_octree_source)
        zox_geter(source, NodeDepth, source_node_depth)
        if (chunkLod->value == 255) {
            chunkLod->value = 0;
        } else {
            chunkLod->value++;
        }
        nodeDepth->value = source_node_depth->value;
        clone_at_depth_ChunkOctree(chunkOctree, chunk_octree_source, chunkLod->value, 0);
        const byte target_depth = nodeDepth->value - min_block_vox_lod;
        if (chunkLod->value == target_depth) {
            zox_geter(source, ChunkSize, source_chunk_size)
            zox_geter(source, ColorRGBs, colors_source)
            const int memory_length = sizeof(color_rgb) * colors_source->length;
            chunkSize->value = source_chunk_size->value;
            colorRGBs->length = colors_source->length;
            colorRGBs->value = memcpy(malloc(memory_length), colors_source->value, memory_length);
            cloneVox->value = 0;
            chunkMeshDirty->value = chunk_dirty_state_trigger;
        }
    }
} zox_declare_system(CloneVoxSystem)