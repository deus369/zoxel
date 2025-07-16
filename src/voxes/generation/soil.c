void build_vox_soil(VoxelNode *voxelNode,
    byte node_depth,
    byte2 voxel_range,
    byte black_voxel_3)
{
    const byte length = powers_of_two_byte[node_depth];
    byte3 size = byte3_single(length);
    fill_new_octree(voxelNode, 0, node_depth);  // clear chunk
    voronoi3D(voxelNode, node_depth, size, voxel_range, black_voxel_3);
    build_vox_noisey(voxelNode, node_depth, voxel_range, black_voxel_3);
}