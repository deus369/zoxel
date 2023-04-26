extern unsigned char is_split_screen;
#ifdef zoxel_ui
    extern ecs_entity_t fps_display;
#endif

#define main_camera_rotation_speed 60 * 0.22f

//! Spawns our first game entities.
void boot_zoxel_game(ecs_world_t *world) {
    zoxel_log(" > [zoxel] begins to boot\n");
    #ifdef zoxel_space
        ecs_entity_t realm = spawn_realm(world);
        ecs_entity_t game = spawn_game(world);
        ecs_set(world, game, RealmLink, { realm });
    #endif
    int2 screen_dimensions2 = screen_dimensions;
    #ifdef zoxel_cameras
        if (is_split_screen) {
            screen_dimensions2.x /= 2;
            set_main_cameras(2);
        }
        float3 camera_begin_position = { 0, 0.0f, 0.0f };
        #ifdef zoxel_voxels
            #ifdef voxels_spawn_terrain
                #ifdef voxel_octrees
                    camera_begin_position = (float3) { 0, 0.26f * 2 * overall_voxel_scale, 0 };
                #else
                    camera_begin_position = (float3) { 0, 0.52f * 2 * overall_voxel_scale, 0 };
                #endif
            #endif
        #endif
        float rot_x = -0.2f;
        float rot_y = -M_PI_2 + M_PI * (rand() % 101) / 100.0f;
        float4 camera_spawn_rotation = quaternion_from_euler((float3) { rot_x, rot_y, 0 });  // quaternion_identity()
        main_cameras[0] = spawn_base_camera(world, camera_begin_position, camera_spawn_rotation, screen_dimensions2, (int2) { });
        #ifdef zoxel_animations
            float4 rotationer = quaternion_from_euler( (float3) { 0, -main_camera_rotation_speed * degreesToRadians, 0 });
            zoxel_set(world, main_cameras[0], EternalRotation, { rotationer });
        #endif
        if (is_split_screen) {
            //! \todo connect a gamepad to this camera
            camera_begin_position.z += 0.4f;
            main_cameras[1] = spawn_base_camera(world, camera_begin_position, quaternion_identity, screen_dimensions2, (int2) { screen_dimensions2.x, 0 });
        }
        spawn_ui_camera(world, screen_dimensions2);
    #endif
    #ifdef zoxel_inputs
        if (!headless) {
            spawn_connected_devices(world);
        }
        // spawn_player_character3D(world, get_main_camera());
    #endif
    #ifdef zoxel_ui
        spawn_canvas(world, screen_dimensions2);
        #ifdef zoxel_texts
            spawn_font_style(world);
        #endif
        #ifdef zoxel_game_ui
            spawn_zoxel_main_menu(world);
        #endif
    #endif
    #ifdef zoxel_voxels
        #ifdef voxels_spawn_terrain
            create_terrain(world);
        #endif
    #endif
    #ifdef zoxel_lines3D
        #ifdef zoxel_terrain_grid
            spawn_terrain_grid(real_chunk_scale);
        #endif
    #endif
    #ifdef zoxel_musics
        spawn_music(world, instrument_piano);
    #endif
    zoxel_log(" > [zoxel] begins to run\n");
}