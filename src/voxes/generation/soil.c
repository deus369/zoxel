void build_vox_soil(VoxelNode *voxelNode,
    byte node_depth,
    byte2 voxel_range,
    byte black_voxel_3,
    byte vregions)
{
    // const byte length = powers_of_two_byte[node_depth];
    // fill_new_octree(voxelNode, 0, node_depth);  // clear chunk
    voronoi3(voxelNode, node_depth, voxel_range, black_voxel_3, vregions);
    vnoise3(voxelNode, node_depth, voxel_range, black_voxel_3);
}