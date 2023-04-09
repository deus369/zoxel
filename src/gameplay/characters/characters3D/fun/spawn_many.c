//ecs_entity_t *characters;
//int characters_count;

void spawn_many_characters3D(ecs_world_t *world) {
    if (vox_files_count == 0) {
        zoxel_log(" - mr penguin not loaded\n");
        return;
    }
    int vox_file_index = rand() % vox_files_count;
    // printf("Spawning %i\n", vox_file_index);
    vox_file vox = vox_files[vox_file_index];
    if (vox.chunks == NULL) {
        zoxel_log(" - mr penguin corrupted\n");
        return;
    }
    zoxel_log(" > spawning many characters [%i]\n", spawn_characters3D_count);
    float cameraY = spawn_many_y * overall_voxel_scale; // ecs_get(world, main_cameras[0], Position3D)->value.y; //  100.0f;
    float radius = spawn_many_radius * overall_voxel_scale; // 16.0f;
    // characters = malloc(sizeof(ecs_entity_t) * spawn_characters3D_count);
    // characters_count = spawn_characters3D_count;
    for (int i = 0; i < spawn_characters3D_count; i++) {
        vox_file_index = rand() % vox_files_count;
        //#ifdef zoxel_test_single_character3Ds
        //    vox_file_index = 0;
        //#endif
        vox = vox_files[vox_file_index];
        float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });
        float3 position = (float3) { spawn_many_offset.x + - radius + ((rand() % 100) / 101.0f) * radius * 2.0f,
            cameraY, spawn_many_offset.z + - radius + ((rand() % 100) / 101.0f) * radius * 2.0f };
        spawn_character3D(world, character3D_prefab, &vox,
            position, rotation, model_scale * overall_voxel_scale, 0);
        // add_to_ecs_entity_t_array_d(characters, e);
    }
}