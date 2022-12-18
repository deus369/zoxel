
extern bool is_split_screen;

//! Spawns our first game entities.
void boot_zoxel_game(ecs_world_t *world)
{
    zoxel_log("Booting [Zoxel]\n");
    update();   // update once? so ui does its thing properly
    // spawn cameras first
    int2 screen_dimensions2 = screen_dimensions;
    if (is_split_screen)
    {
        screen_dimensions2.x /= 2;
        set_main_cameras(2);
    }
    main_cameras[0] = spawn_base_camera(world, (float3) { 0, 3.6f, 0.62f },
        quaternion_identity(), screen_dimensions2, (int2) { });
    if (is_split_screen)
    {
        //! \todo connect a gamepad to this camera
        main_cameras[1] = spawn_base_camera(world, (float3) { 0, 3.6f, 1.62f },
            quaternion_identity(), screen_dimensions2, (int2) { screen_dimensions2.x, 0 });
    }
    spawn_ui_camera(world, screen_dimensions2);
    // spawn devices
    spawn_connected_devices(world);
    // spawn font, canvas and ui
    spawn_font_style(world);
    spawn_canvas(world, screen_dimensions2);
    // test ui line
    color edge_color = (color) { 8, 3, 3, 255 };
    // color cross_color =  (color) { 55, 33, 12, 255 };
    float edge_size = 32.0f;
    spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { screen_dimensions.x, 0 }, edge_color, edge_size, 0.0);
    spawn_ui_line2D(world, main_canvas, (int2) { screen_dimensions.x, 0 }, (int2) { screen_dimensions.x, screen_dimensions.y }, edge_color, edge_size, 0.0);
    spawn_ui_line2D(world, main_canvas, (int2) { screen_dimensions.x, screen_dimensions.y }, (int2) { 0, screen_dimensions.y }, edge_color, edge_size, 0.0);
    spawn_ui_line2D(world, main_canvas, (int2) { 0, screen_dimensions.y }, (int2) { 0, 0 }, edge_color, edge_size, 0.0);
    // spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { 1920, 1080 }, cross_color, 4.0f, 0.0);
    // spawn_ui_line2D(world, main_canvas, (int2) { 0, 1080 }, (int2) { 1920, 0 }, cross_color, 4.0f, 0.0);
    #ifdef zoxel_test_uis
    spawn_test_uis(world);   // spawns test ui
    #endif
    // spawn_player_character3D(world, get_main_camera());
    spawn_zoxel_main_menu(world);
    fps_display = spawn_fps_display(world, main_canvas, 32);
}