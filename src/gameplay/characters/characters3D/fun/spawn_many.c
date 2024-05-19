void spawn_many_characters3D(ecs_world_t *world) {
    if (vox_files_count == 0) {
        zoxel_log(" - mr penguin not loaded\n");
        return;
    }
    int vox_file_index = rand() % vox_files_count;
    vox_file vox = vox_files[vox_file_index];
    if (vox.chunks == NULL) {
        zoxel_log(" - mr penguin corrupted\n");
        return;
    }
    zoxel_log(" > spawning many characters [%i]\n", spawn_characters3D_count);
    float cameraY = spawn_many_y * overall_voxel_scale;
    float radius = spawn_many_radius * overall_voxel_scale;
    for (int i = 0; i < spawn_characters3D_count; i++) {
        vox_file_index = rand() % vox_files_count;
        vox = vox_files[vox_file_index];
        float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });
        float3 position = (float3) { spawn_many_offset.x + - radius + ((rand() % 100) / 101.0f) * radius * 2.0f, cameraY, spawn_many_offset.z + - radius + ((rand() % 100) / 101.0f) * radius * 2.0f };
        spawn_character3D(world, prefab_character3D, &vox, position, rotation, 0, 0, 0, 0);
    }
}
