extern unsigned char is_split_screen;
#ifdef zoxel_ui
    extern ecs_entity_t fps_display;
#endif
#define main_camera_rotation_speed 60 * 0.22f
const char *icon_filepath;

unsigned char boot_zoxel_game(ecs_world_t *world) {
    // zoxel_log(" > [zoxel] begins to boot\n");
    // todo: initialize_engine
    if (initialize_pathing() == EXIT_FAILURE) return EXIT_FAILURE;
    zoxel_log(" > [zoxel] success initializing pathing\n");
    if (initialize_apps(world) == EXIT_FAILURE) return EXIT_FAILURE;
    zoxel_log(" > [zoxel] success initializing app\n");
    if (initialize_rendering(world) == EXIT_FAILURE) return EXIT_FAILURE;
    zoxel_log(" > [zoxel] success initializing rendering\n");
    load_resources_engine(world);

    icon_filepath = resources_folder_name"textures/game_icon.png";
    // zoxel_log(" > icon_filepath set to [%s]\n", icon_filepath);
    load_app_icon(main_window, icon_filepath);

    // zoxel_log(" > [zoxel] success initializing sdl window\n");
    ecs_entity_t realm = 0;
    #ifdef zoxel_include_players
        realm = spawn_realm(world);
        ecs_entity_t game = spawn_game(world);
        zox_set_only(game, RealmLink, { realm })
        spawn_weather(world);
    #endif
    int2 screen_dimensions2 = screen_dimensions;
    float3 camera_begin_position = { 0, 0.0f, 0.0f };
    #ifdef zoxel_cameras
        if (is_split_screen) {
            screen_dimensions2.x /= 2;
            set_main_cameras(2);
        }
        #ifdef zoxel_voxels
            #ifndef zox_disable_terrain
                #ifndef zox_disable_terrain_octrees
                    camera_begin_position = (float3) { 0, 0.32f * overall_voxel_scale, 0 };
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
            zox_set(main_cameras[0], EternalRotation, { rotationer });
        #endif
        if (is_split_screen) {
            //! \todo connect a gamepad to this camera
            camera_begin_position.z += 0.4f;
            main_cameras[1] = spawn_base_camera(world, camera_begin_position, quaternion_identity, screen_dimensions2, (int2) { screen_dimensions2.x, 0 });
        }
        spawn_ui_camera(world, screen_dimensions2);
    #endif
    #ifdef zoxel_inputs
        if (!headless) spawn_connected_devices(world);
        // spawn_player_character3D(world, get_main_camera());
    #endif
    #ifdef zoxel_players
        if (!headless) {
            ecs_entity_t player = spawn_player(world);
            zox_set_only(player, CameraLink, { main_cameras[0] })
        }
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
        #ifndef zox_disable_terrain
            ecs_entity_t terrain = create_terrain(world);
            #ifdef zoxel_space
                zox_set_only(terrain, RealmLink, { realm })
            #endif
        #endif
    #endif
    #ifdef zoxel_lines3D
        #ifdef zox_disable_terrain_grid
            spawn_terrain_grid(real_chunk_scale);
        #endif
    #endif
    #ifdef zoxel_musics
        if (!headless) spawn_music(world, instrument_piano); // _square
    #endif
    #ifdef zox_test_voxel_mesh
        test_animating_chunks(world, camera_begin_position);
    #endif
    #ifdef zox_test_voxes
        test_voxes(world, camera_begin_position);
    #endif
    // zoxel_log(" > [zoxel] begins to run\n");
    return EXIT_SUCCESS;
}