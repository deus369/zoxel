//! =-= Zoxel =-=
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define SDL_IMAGES
#include "zoxel_flecs.c"
#include "zoxel.c"

// Settings 
extern bool headless;
extern bool running;
extern bool profiler;
extern float4x4 mainCameraMatrix;  //! Used globally in render systems
ecs_entity_t localPlayer;

//! Spawns our first game entities.
void spawn_game()
{
    SpawnMainCamera(screenDimensions);
    SpawnKeyboardEntity();
    SpawnMouseEntity();
    localPlayer = SpawnPlayerCharacter2D(world);
}

//! Temporarily runs render things on main thread until flecs bug is fixed.
void render_loop_temp()
{
    //clock_t t = clock();
    const FreeRoam *freeRoam = ecs_get(world, mainCamera, FreeRoam);
    mainCameraMatrix = ecs_get(world, mainCamera, ViewMatrix)->value;
    SDL_SetRelativeMouseMode(freeRoam->value);  //! Locks Main Mouse.
    TextureUpdateMainThread();  // uploads textures to gpu
    // now render the things
    OpenGLClear();
    OpenGLBeginInstancing(mainCameraMatrix);
    ecs_run(world, ecs_id(InstanceRender2DSystem), 0, NULL);
    OpenGLEndInstancing();
    // seperate materials 2D
    ecs_run(world, ecs_id(RenderMaterial2DSystem), 0, NULL);
    // 3D instancing
    OpenGLBeginInstancing3D(mainCameraMatrix);
    ecs_run(world, ecs_id(InstanceRender3DSystem), 0, NULL);
    OpenGLEndInstancing3D();
    UpdateLoopSDL();
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
    ResetDevices(world);
    SDL_Event event  = { 0 };
    while (SDL_PollEvent(&event))
    {
        ExtractKeyboard(world, event);
        ExtractMouseEvent(world, event);
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
            // test
            else if (key == SDLK_z) 
            {
                const ScreenDimensions *screenDimensions = ecs_get(world, mainCamera, ScreenDimensions);
                const Position *cameraPosition = ecs_get(world, mainCamera, Position);
                const Rotation *cameraRotation = ecs_get(world, mainCamera, Rotation);
                float3 cameraEuler = quaternion_to_euler(cameraRotation->value);
                printf("Le Camera\n");
                printf("    - Dimensions %ix%i\n", screenDimensions->value.x, screenDimensions->value.y);
                printf("    - Position [x:%f y:%f z:%f]\n", cameraPosition->value.x, cameraPosition->value.y, cameraPosition->value.z);
                printf("    - Euler [x:%f y:%f z:%f]\n", cameraEuler.x, cameraEuler.y, cameraEuler.z);
                // printf("Update Player Character Texture.\n");
                // ecs_set(world, localPlayer, GenerateTexture, { 1 });
                // TestDestroyTexture(world);
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
    BeginAppECS(argc, argv, profiler);
    SetMultiThreading();
    // import game modules
    ECS_IMPORT(world, Zoxel);
    spawn_game();
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&update, -1, 1); // old - 60, 1);
#else
    while (running)
    {
        update();
    }
#endif
    EndAppECS();
    if (!headless)
    {
        EndAppOpenGL();
        EndAppSDL();
    }
    return 0;
}