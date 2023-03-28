void spawn_many_characters3D(ecs_world_t *world) {
    int vox_file_index = rand() % vox_files_count;
    // printf("Spawning %i\n", vox_file_index);
    vox_file vox = vox_files[vox_file_index];
    zoxel_log("spawn_many_characters3D [%i]\n", spawn_characters3D_count);
    const float model_scale = 0.015f;
    float cameraY = 1.02f * overall_voxel_scale; // ecs_get(world, main_cameras[0], Position3D)->value.y; //  100.0f;
    float radius = 0.5f * overall_voxel_scale; // 16.0f;
    for (int i = 0; i < spawn_characters3D_count; i++) {
        float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });
        float3 position = (float3) { - radius + (rand() % 100) / 101.0f * radius * 2.0f,
            cameraY, - radius + (rand() % 100) / 101.0f * radius * 2.0f };
        spawn_character3D(world, character3D_prefab, &vox, position, rotation, model_scale);
    }
}