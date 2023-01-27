

int3 voxel_chunk_position(int3 chunk_position, int3 chunk_size)
{
    int3 voxel_position = int3_multiply_int3(chunk_position, chunk_size);
    if (voxel_position.x < 0)
    {
        voxel_position.x += 1;
    }
    if (voxel_position.y < 0)
    {
        voxel_position.y += 1;
    }
    if (voxel_position.z < 0)
    {
        voxel_position.z += 1;
    }
    return voxel_position;
}

int3 voxel_chunk_position_xz(int3 chunk_position, int3 chunk_size)
{
    int3 voxel_position = int3_multiply_int3(chunk_position, chunk_size);
    if (voxel_position.x < 0)
    {
        voxel_position.x += 1;
    }
    if (voxel_position.z < 0)
    {
        voxel_position.z += 1;
    }
    return voxel_position;
}