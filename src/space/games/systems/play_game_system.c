//! Closes the game when button is clicked.
void PlayGameSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const GenericEvent *genericEvents = ecs_field(it, GenericEvent, 1);
    for (int i = 0; i < it->count; i++) {
        const GenericEvent *genericEvent = &genericEvents[i];
        if (genericEvent->value == 1) {
            zoxel_log(" > game play begins [%lu]\n", it->entities[i]);
            // destroy ai camera
            ecs_entity_t first_camera = main_cameras[0];
            float3 first_camera_position = ecs_get(world, first_camera, Position3D)->value;
            float4 first_camera_rotation = ecs_get(world, first_camera, Rotation3D)->value;
            float4x4 first_view_matrix = ecs_get(world, first_camera, ViewMatrix)->value;
            int2 first_camera_screen_dimensions = ecs_get(world, first_camera, ScreenDimensions)->value;
            ecs_delete(world, first_camera);
            // spawn free roam camera
            // \todo I believe the flickering is due to the matrix not being set in time.
            main_cameras[0] = spawn_free_camera(world, first_camera_position, // (float3) { 0, 3.6f, 0.62f },
                first_camera_rotation, first_camera_screen_dimensions, (int2) { });
            ecs_set(world, main_cameras[0], ViewMatrix, { first_view_matrix });
            ecs_add(world, main_cameras[0], Streamer);
            ecs_add(world, main_cameras[0], StreamPoint);
            ecs_set(world, main_cameras[0], VoxLink, { main_terrain_world });
            main_camera_matrix = first_view_matrix;
            attach_to_character(world, main_cameras[0], main_character3D);
            // \todo Fix issue with rotation, due to euler setting, make sure to set euler when spawning cameras
            #ifdef voxels_spawn_terrain
            //    create_terrain(world);
            #endif
            #ifdef zoxel_spawn_character3Ds
                spawn_many_characters3D(world);
            #endif
        }
    }
}
zoxel_declare_system(PlayGameSystem)