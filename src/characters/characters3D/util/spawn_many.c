void spawn_many_characters3D(ecs_world_t *world) {
    /*if (files_voxes_count == 0) {
        return;
    }
    int vox_file_index = rand() % files_voxes_count;
    vox_file vox = files_voxes[vox_file_index];
    if (vox.chunks == NULL) {
        return;
    }
    float cameraY = spawn_many_y * overall_voxel_scale;
    float radius = spawn_many_radius * overall_voxel_scale;
    for (int i = 0; i < spawn_characters3D_count; i++) {
        vox_file_index = rand() % files_voxes_count;
        vox = files_voxes[vox_file_index];
        float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });
        float3 position = (float3) { spawn_many_offset.x + - radius + ((rand() % 100) / 101.0f) * radius * 2.0f, cameraY, spawn_many_offset.z + - radius + ((rand() % 100) / 101.0f) * radius * 2.0f };
        spawn_character3(world, pref=ab_character3D, &vox, position, rotation, 0, 0, 0, 0);
    }*/
}
