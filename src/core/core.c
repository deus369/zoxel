#ifndef zoxel_core
#define zoxel_core

#ifdef zoxel_time_render_loop
#include <time.h>
const double min_render_loop_timing = 0;    // set to higher to check for spikes
#endif

// Settings for main
bool headless = false;
bool running = true;
bool profiler = false;
// --- core ---
#include "maths/maths.c"
#include "generic/generic.c"
#include "apps/apps.c"
#include "inputs/inputs.c"
#include "timing/timing.c"
#include "transforms/transforms.c"
#include "rendering/rendering.c"
#include "cameras/cameras.c"

extern void texture_update_main_thread();

//! Temporarily runs render things on main thread until flecs bug is fixed.
void render_loop_temp()
{
    #ifdef zoxel_time_render_loop
    clock_t t = clock();
    #endif
    ecs_entity_t main_camera = get_main_camera();
    if (!ecs_is_valid(world, main_camera))
    {
        return;
    }
    const FreeRoam *freeRoam = ecs_get(world, main_camera, FreeRoam);
    main_camera_matrix = ecs_get(world, main_camera, ViewMatrix)->value;
    ui_camera_matrix = ecs_get(world, cameras[1], ViewMatrix)->value;
    SDL_SetRelativeMouseMode(freeRoam->value);  //! Locks Main Mouse.
    texture_update_main_thread();  // uploads textures to gpu
    mesh_update_main_thread();
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
    
    finish_opengl_rendering(world);
    #ifdef zoxel_time_render_loop
    t = clock() - t;
    double t2 =  (((double) 1000.0 * t) / CLOCKS_PER_SEC);
    if (t2 >= min_render_loop_timing)
    {
        printf("Render Time [%fms]\n", t2);
    }
    #endif
}

void CoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, Core);
    ECS_IMPORT(world, Generic);
    ECS_IMPORT(world, Maths);
    if (!headless)
    {
        ECS_IMPORT(world, Apps);
    }
    ECS_IMPORT(world, Inputs);
    ECS_IMPORT(world, Timing);
    ECS_IMPORT(world, Transforms);
    if (!headless)
    {
        ECS_IMPORT(world, Rendering);
    }
    ECS_IMPORT(world, Cameras);
}

#endif