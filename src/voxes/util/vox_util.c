

// todo: make this a update function so it does one node at a time! load per entity per depth level to slow it down
void clone_vox_data(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t source, byte max_depth) {
    if (!source) return;
    const int3 chunk_size = zox_get_value(source, ChunkSize)
    zox_set(e, ChunkSize, { chunk_size })
    zox_geter(source, ChunkOctree, chunk_octree_source)
    zox_get_muter(e, ChunkOctree, dest)
    zox_geter(source, ColorRGBs, colors_source)
    zox_get_muter(e, ColorRGBs, colors_dest)
    // clone_ChunkOctree(dest, chunk_octree_source);
    dest->linked = chunk_octree_source->linked;
    clone_depth_ChunkOctree(dest, chunk_octree_source, max_depth, 0);
    colors_dest->length = colors_source->length;
    const int memory_length = sizeof(color_rgb) * colors_dest->length;
    colors_dest->value = memcpy(malloc(memory_length), colors_source->value, memory_length);
}