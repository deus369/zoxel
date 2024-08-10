void CloneVoxSystem(ecs_iter_t *it) {
    zox_field_in(CloneVoxLink, cloneVoxLinks, 1)
    zox_field_out(CloneVox, cloneVoxes, 2)
    zox_field_out(ChunkOctree, chunkOctrees, 3)
    zox_field_out(ChunkSize, chunkSizes, 4)
    zox_field_out(ColorRGBs, colorRGBss, 5)
    zox_field_out(ChunkDirty, chunkDirtys, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(CloneVox, cloneVoxes, cloneVox)
        if (!cloneVox->value) continue;
        zox_field_i(CloneVoxLink, cloneVoxLinks, cloneVoxLink)
        const ecs_entity_t source = cloneVoxLink->value;
        if (!source) {
            continue;
        }
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_o(ColorRGBs, colorRGBss, colorRGBs)
        zox_field_o(ChunkSize, chunkSizes, chunkSize)
        zox_field_o(ChunkDirty, chunkDirtys, chunkDirty)
        zox_geter(source, ChunkSize, source_chunk_size)
        zox_geter(source, ChunkOctree, chunk_octree_source)
        zox_geter(source, ColorRGBs, colors_source)
        const int memory_length = sizeof(color_rgb) * colors_source->length;
        const unsigned char clone_depth = 1 + max_octree_depth - min_block_vox_lod;
        clone_depth_ChunkOctree(chunkOctree, chunk_octree_source, clone_depth, 0);
        chunkSize->value = source_chunk_size->value;
        colorRGBs->length = colors_source->length;
        colorRGBs->value = memcpy(malloc(memory_length), colors_source->value, memory_length);

        cloneVox->value = 0;
        chunkDirty->value = chunk_dirty_state_generated;
    }
} zox_declare_system(CloneVoxSystem)
