void test_voxes(ecs_world_t *world, float3 position) {
    vox_file vox = vox_files[3];
    spawn_vox(world, &vox, (float3) { position.x - 3, position.y, position.z + 1 }, 4);
    spawn_vox(world, &vox, (float3) { position.x - 1.5f, position.y, position.z + 1 }, 3);
    spawn_vox(world, &vox, (float3) { position.x, position.y, position.z + 1 }, 2);
    spawn_vox(world, &vox, (float3) { position.x + 1.5f, position.y, position.z + 1 }, 1);
    spawn_vox(world, &vox, (float3) { position.x + 3, position.y, position.z + 1 }, 0);
}
