//! =-= Zoxel =-=
#define SDL_IMAGES
// #define zoxel_test_character2Ds
// #define zoxel_test_cubes
// #define zoxel_test_voxels
#define zoxel_test_uis
#include "_includes.c"

ecs_entity_t localPlayer;
extern bool headless;
extern bool running;
extern bool profiler;
extern float4x4 main_camera_matrix;  //! Used globally in render systems

//! Spawns our first game entities.
void spawn_game(ecs_world_t *world)
{
    ecs_entity_t main_camera = spawn_main_camera(world, screenDimensions);
    spawn_ui_camera(world, screenDimensions);
    spawn_connected_devices(world);
    localPlayer = spawn_player_character2D(world, main_camera);
    spawn_main_menu(world, "Zoxel");
}

//! The main update loop.
void update()
{
    // apps / Input events
    if (!headless)
    {
        reset_input_devices(world);
        update_sdl(world);
        #ifdef __EMSCRIPTEN__
        if (update_web_canvas())
        {
            return;
        }
        #endif
    }
    // ecs_log_set_level(1);    // use this to debug system pipelines
    ecs_progress(world, 0);
    if (!headless)
    {
        render_loop_temp();
    }
}

//! Includes special case for emscripten.
void main_loop()
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&update, -1, 1); // old - 60, 1);
#else
    while (running)
    {
        update();
    }
#endif
}

//! Where it all begins and ends.
int main(int argc, char* argv[])
{
    int didFail = process_arguments(argc, argv);
    if (didFail == EXIT_FAILURE)
    {
        return EXIT_SUCCESS;
    }
    open_ecs(argc, argv, profiler); // begin ecs
    ECS_IMPORT(world, Zoxel);       // import game modules
    spawn_game(world);              // spawn game entities
    main_loop();
    close_ecs();
    if (!headless)
    {
        dispose_opengl();
        sdl_on_end();
    }
    return 0;
}