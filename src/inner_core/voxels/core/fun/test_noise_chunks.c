void test_noise_chunks() {
    spawn_voxel_noise_chunk_mesh(world, prefab_noise_chunk, (float3) { 0, 0, 0 }, 0.15f);
    spawn_voxel_noise_chunk_mesh(world, prefab_noise_chunk, (float3) { 0, -spawnRange, 0 }, 0.05f);
    spawn_voxel_noise_chunk_mesh(world, prefab_noise_chunk, (float3) { 0, spawnRange, 0 }, 0.05f);
    spawn_voxel_noise_chunk_mesh(world, prefab_noise_chunk, (float3) { -spawnRange, 0, 0 }, 0.05f);
    spawn_voxel_noise_chunk_mesh(world, prefab_noise_chunk, (float3) { spawnRange, 0, 0 }, 0.05f);
}