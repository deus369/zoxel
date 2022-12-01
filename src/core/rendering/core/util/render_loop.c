// timing the render loop
#ifdef zoxel_time_render_loop
#include <time.h>
const double min_render_loop_timing = 0;    // set to higher to check for spikes
#endif

// extern ecs_entity_t get_main_camera();

void render_camera(ecs_world_t *world, float4x4 camera_matrix, int2 position, int2 size)
{
    main_camera_matrix = camera_matrix;
    // GL.Viewport(0, 0, window.Width / 2, window.Height);
    #ifndef __EMSCRIPTEN__
    glViewport(position.x, position.y, size.x, size.y);
    #endif
    // 3D renders
    OpenGLBeginInstancing3D(main_camera_matrix);
    ecs_run(world, ecs_id(InstanceRender3DSystem), 0, NULL);
    opengl_disable_opengl_program();
    ecs_run(world, ecs_id(Render3DSystem), 0, NULL);
    ecs_run(world, ecs_id(Render3DUvsSystem), 0, NULL);
    // 2D renders
    glDisable(GL_DEPTH_TEST);
    OpenGLBeginInstancing(main_camera_matrix);
    ecs_run(world, ecs_id(InstanceRender2DSystem), 0, NULL);
    opengl_disable_opengl_program();
    ecs_run(world, ecs_id(RenderMaterial2DSystem), 0, NULL);
    ecs_run(world, ecs_id(RenderMeshMaterial2DSystem), 0, NULL);
}

//! Temporarily runs render things on main thread until flecs bug is fixed.
void render_loop_temp()
{
    #ifdef zoxel_time_render_loop
    clock_t t = clock();
    #endif
    // upload meshes to gpu
    mesh_update_main_thread();
    mesh_uvs_update_main_thread();
    // now render the things
    opengl_clear();
    // camera renders
    if (ecs_is_valid(world, ui_cameras[0]))
    {
        ui_camera_matrix = ecs_get(world, ui_cameras[0], ViewMatrix)->value;
    }
    for (int i = 0; i < main_cameras_count; i++)
    {
        ecs_entity_t camera = main_cameras[i];
        if (ecs_is_valid(world, camera))
        {
            render_camera(world,
                ecs_get(world, camera, ViewMatrix)->value,
                ecs_get(world, camera, ScreenPosition)->value,
                ecs_get(world, camera, ScreenDimensions)->value);
        }
    }
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