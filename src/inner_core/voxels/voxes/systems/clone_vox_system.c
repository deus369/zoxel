// todo: make use TargetChunkLod -> and load/unload depth based on that
// todo: set lod here instead of just applying RenderLod only with ChunkDirty -> keeps memory down

void CloneVoxSystem(ecs_iter_t *it) {
    zox_field_in(CloneVoxLink, cloneVoxLinks, 1)
    zox_field_out(CloneVox, cloneVoxes, 2)
    zox_field_out(ChunkOctree, chunkOctrees, 3)
    zox_field_out(ChunkSize, chunkSizes, 4)
    zox_field_out(ColorRGBs, colorRGBss, 5)
    zox_field_out(ChunkDirty, chunkDirtys, 6)
    zox_field_out(ChunkLod, chunkLods, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(CloneVox, cloneVoxes, cloneVox)
        if (!cloneVox->value) continue;
        zox_field_i(CloneVoxLink, cloneVoxLinks, cloneVoxLink)
        const ecs_entity_t source = cloneVoxLink->value;
        if (!source) continue;
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_o(ColorRGBs, colorRGBss, colorRGBs)
        zox_field_o(ChunkSize, chunkSizes, chunkSize)
        zox_field_o(ChunkDirty, chunkDirtys, chunkDirty)
        zox_field_o(ChunkLod, chunkLods, chunkLod)
        // clone one depth at a time
        zox_geter(source, ChunkOctree, chunk_octree_source)
        if (chunkLod->value == 255) chunkLod->value = 0;
        else chunkLod->value++;
        clone_at_depth_ChunkOctree(chunkOctree, chunk_octree_source, chunkLod->value, 0);
        // should be about 5!
        const unsigned char target_depth = max_octree_depth - min_block_vox_lod;
        if (chunkLod->value == target_depth) {
            zox_geter(source, ChunkSize, source_chunk_size)
            zox_geter(source, ColorRGBs, colors_source)
            const int memory_length = sizeof(color_rgb) * colors_source->length;
            chunkSize->value = source_chunk_size->value;
            colorRGBs->length = colors_source->length;
            colorRGBs->value = memcpy(malloc(memory_length), colors_source->value, memory_length);
            cloneVox->value = 0;
            chunkDirty->value = chunk_dirty_state_generated;
        }
    }
} zox_declare_system(CloneVoxSystem)
