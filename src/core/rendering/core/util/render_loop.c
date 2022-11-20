#ifdef zoxel_time_render_loop
#include <time.h>
const double min_render_loop_timing = 0;    // set to higher to check for spikes
#endif

extern ecs_entity_t get_main_camera();

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
    main_camera_matrix = ecs_get(world, main_camera, ViewMatrix)->value;
    ui_camera_matrix = ecs_get(world, cameras[1], ViewMatrix)->value;
    // upload meshes to gpu
    mesh_update_main_thread();
    mesh_uvs_update_main_thread();
    // now render the things
    opengl_clear();
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