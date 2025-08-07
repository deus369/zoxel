// todo: make this a update function so it does one node at a time! load per entity per depth level to slow it down
void clone_vox_data(ecs *world,
    const entity e,
    const entity source,
    byte max_depth)
{
    if (!source) {
        return;
    }
    const int3 chunk_size = zox_get_value(source, ChunkSize)
    zox_set(e, ChunkSize, { chunk_size })
    zox_geter(source, VoxelNode, chunk_octree_source)
    zox_geter(source, NodeDepth, source_node_depth)
    zox_geter(source, ColorRGBs, colors_source)
    zox_get_muter(e, VoxelNode, dest)
    zox_get_muter(e, NodeDepth, nodeDepth)
    zox_get_muter(e, ColorRGBs, colors_dest)
    // clone_VoxelNode(dest, chunk_octree_source);
    nodeDepth->value = source_node_depth->value;
    clone_depth_VoxelNode(dest, chunk_octree_source, max_depth, 0);
    colors_dest->length = colors_source->length;
    const int memory_length = sizeof(color_rgb) * colors_dest->length;
    colors_dest->value = memcpy(malloc(memory_length), colors_source->value, memory_length);
}