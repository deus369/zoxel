//! =-= Zoxel =-=
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define SDL_IMAGES
#include "zoxel_flecs.c"
#define zoxel_test_character2Ds
#define zoxel_test_cubes
#define zoxel_test_voxels
#include "zoxel.c"

// Settings 
extern bool headless;
extern bool running;
extern bool profiler;
extern float4x4 main_camera_matrix;  //! Used globally in render systems
ecs_entity_t localPlayer;

//! Spawns our first game entities.
void spawn_game(ecs_world_t *world)
{
    ecs_entity_t main_camera = spawn_main_camera(world, screenDimensions);
    spawn_ui_camera(world, screenDimensions);
    SpawnKeyboardEntity();
    SpawnMouseEntity();
    localPlayer = spawn_player_character2D(world, main_camera);
    
    // test ui
    int2 testSize = { 32, 32 };
    int2 actionbar_size4 = (int2) { 420, 54 };
    int2 testSize2 = (int2) { 48, 48 };
    // spawn_element(world, (int2) { screenDimensions.x / 2, screenDimensions.y / 2 }, testSize);   // crosshair
    spawn_element(world, (int2) { testSize.x / 2, testSize.y / 2 }, testSize);
    spawn_element(world, (int2) { screenDimensions.x - testSize.x / 2, testSize.y / 2 }, testSize);
    spawn_element(world, (int2) { testSize.x / 2, screenDimensions.y - testSize.y / 2 }, testSize);
    spawn_element(world, (int2) { screenDimensions.x - testSize.x / 2, screenDimensions.y - testSize.y / 2 }, testSize);
    spawn_element(world, (int2) { screenDimensions.x / 2, 10 + actionbar_size4.y / 2 }, actionbar_size4);
    // actionbar
    spawn_element(world, (int2) { screenDimensions.x / 2, 10 + actionbar_size4.y / 2 }, testSize2);
    spawn_element(world, (int2) { screenDimensions.x / 2 - 3 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2);
    spawn_element(world, (int2) { screenDimensions.x / 2 + 3 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2);
    spawn_element(world, (int2) { screenDimensions.x / 2 - 6 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2);
    spawn_element(world, (int2) { screenDimensions.x / 2 + 6 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2);


    // test horizontal by spawning one per bar
    /*int width_division = 2; // 16;
    int height_division = 32; // 16;
    int bar_width = screenDimensions.x / width_division; // 64;
    int bar_height = screenDimensions.y / height_division; // 64;
    int width_tests = 1 + screenDimensions.x / bar_width;
    int height_tests = 1 + screenDimensions.y / bar_height;
    for (int i = 0; i < height_tests; i++)
    {
        for (int j = 0; j < width_tests; j++)
        {
            spawn_element(world,
                (int2) { j * bar_width + bar_width / 2, i * bar_height + bar_height / 2 },
                (int2) { bar_width, bar_height });
        }
    }*/
}

//! Temporarily runs render things on main thread until flecs bug is fixed.
void render_loop_temp()
{
    //clock_t t = clock();
    ecs_entity_t main_camera = get_main_camera();
    const FreeRoam *freeRoam = ecs_get(world, main_camera, FreeRoam);
    main_camera_matrix = ecs_get(world, main_camera, ViewMatrix)->value;
    ui_camera_matrix = ecs_get(world, cameras[1], ViewMatrix)->value;
    SDL_SetRelativeMouseMode(freeRoam->value);  //! Locks Main Mouse.
    TextureUpdateMainThread();  // uploads textures to gpu
    MeshUpdateMainThread();
    // now render the things
    OpenGLClear();
    OpenGLBeginInstancing(main_camera_matrix);
    ecs_run(world, ecs_id(InstanceRender2DSystem), 0, NULL);
    OpenGLEndInstancing();

    // 3D instancing
    OpenGLBeginInstancing3D(main_camera_matrix);
    ecs_run(world, ecs_id(InstanceRender3DSystem), 0, NULL);
    OpenGLEndInstancing3D();
    // seperate materials 3D mesh
    ecs_run(world, ecs_id(Render3DUniqueSystem), 0, NULL);

    // seperate materials 2D
    ecs_run(world, ecs_id(RenderMaterial2DSystem), 0, NULL);
    ecs_run(world, ecs_id(RenderMaterial2DScale2DSystem), 0, NULL);
    ecs_run(world, ecs_id(RenderMeshMaterial2DSystem), 0, NULL);
    
    finish_opengl_rendering();
    //t = clock() - t;
    //printf("Render Time [%fms]\n", (((double) 1000.0 * t)/CLOCKS_PER_SEC));
}

//! Quits the application from running indefinitely.
void quit()
{
    running = false;
    #ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    #endif
}

//! Polls SDL for input events. Also handles resize and window quit events.
void poll_sdl()
{
    reset_input_devices(world);
    SDL_Event event  = { 0 };
    while (SDL_PollEvent(&event))
    {
        input_extract_from_sdl(world, event);
        int eventType = event.type;
        if (eventType == SDL_QUIT)
        {
            quit();
        }
        else if (eventType == SDL_KEYUP)
        {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_ESCAPE) 
            {
                quit();
            }
        }
        else if (eventType == SDL_WINDOWEVENT)
        {
            // printf("SDL_WINDOWEVENT Window Event!");
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                ResizeOpenGLViewport(event.window.data1, event.window.data2);
                ResizeCameras(event.window.data1, event.window.data2);
            }
            else if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                ResizeOpenGLViewport(event.window.data1, event.window.data2);
                ResizeCameras(event.window.data1, event.window.data2);
            }
        }
    }
}

//! Convert starting arguments to Settings.
int process_arguments(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            PrintHelpMenu(argv[0]);
            return EXIT_FAILURE;
        }
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fullscreen") == 0)
        {
            fullscreen = true;
        }
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vsync") == 0)
        {
            vsync = true;
        }
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--profiler") == 0)
        {
            profiler = true;
        }
        if (strcmp(argv[i], "-z") == 0 || strcmp(argv[i], "--headless") == 0)
        {
            headless = true;
        }
    }
    return EXIT_SUCCESS;
}

//! The main update loop.
void update()
{
    // apps / Input events
    if (!headless)
    {
        poll_sdl();
        #ifdef __EMSCRIPTEN__
        if (UpdateWebCanvas())
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

//! Where it all begins and ends.
int main(int argc, char* argv[])
{
    int didFail = process_arguments(argc, argv);
    if (didFail == EXIT_FAILURE)
    {
        return EXIT_SUCCESS;
    }
    open_ecs(argc, argv, profiler);
    // import game modules
    ECS_IMPORT(world, Zoxel);
    spawn_game(world);
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&update, -1, 1); // old - 60, 1);
#else
    while (running)
    {
        update();
    }
#endif
    close_ecs();
    if (!headless)
    {
        EndAppOpenGL();
        EndAppSDL();
    }
    return 0;
}

            // test
            /*else if (key == SDLK_z) 
            {
                const ScreenDimensions *screenDimensions = ecs_get(world, main_camera, ScreenDimensions);
                const Position *cameraPosition = ecs_get(world, main_camera, Position);
                const Rotation *cameraRotation = ecs_get(world, main_camera, Rotation);
                float3 cameraEuler = quaternion_to_euler(cameraRotation->value);
                printf("Le Camera\n");
                printf("    - Dimensions %ix%i\n", screenDimensions->value.x, screenDimensions->value.y);
                printf("    - Position [x:%f y:%f z:%f]\n", cameraPosition->value.x, cameraPosition->value.y, cameraPosition->value.z);
                printf("    - Euler [x:%f y:%f z:%f]\n", cameraEuler.x, cameraEuler.y, cameraEuler.z);
                // printf("Update Player Character Texture.\n");
                // ecs_set(world, localPlayer, GenerateTexture, { 1 });
                // TestDestroyTexture(world);
                // const Rotation *test_mesh_rotation = ecs_get(world, custom_mesh, Rotation);
                // float3 test_mesh_euler = quaternion_to_euler(test_mesh_rotation->value);
                // test_mesh_euler = float3_divide_float(test_mesh_euler, degreesToRadians);
                // printf("    - test_mesh_euler [x:%f y:%f z:%f]\n", test_mesh_euler.x, test_mesh_euler.y, test_mesh_euler.z);
            }*/