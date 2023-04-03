int render_queue_count = 0;
const unsigned char max_render_layers = 8;
unsigned char renderer_layer;
#ifdef zoxel_lines3D
    extern long int line3D_render_system_id;
#endif
extern long int element_mesh_system_id;
extern long int texture_update_system_id;
extern long int mesh_uvs_update_system_id;
extern int mesh_update_pipeline2;
// \todo Create a queue of 3D models to render, including materials, etc
//  - each type of render queue has different data based on the shaders
//  - inside ecs systems, can run multithread, add things to queues to render
// zoxel_declare_system(RenderMaterial2DSystem);

void render_pre_loop() {
    opengl_clear();             // cannot just clear in a view port with opengl?
    render_queue_count = 0;
}

//! This renders all render systems per camera, by externally setting the camera matrix this will be uploaded to all materials.
void render_camera(ecs_world_t *world, float4x4 camera_matrix, int2 position, int2 size) {
    main_camera_matrix = camera_matrix;
    glViewport(position.x, position.y, size.x, size.y);
    opengl_instance3D_begin(main_camera_matrix);
    if (render3D_update_pipeline == 0) {
        ecs_run(world, ecs_id(InstanceRender3DSystem), 0, NULL);
        opengl_disable_opengl_program();
        ecs_run(world, ecs_id(Render3DSystem), 0, NULL);
        ecs_run(world, ecs_id(Render3DUvsSystem), 0, NULL);
        #ifdef zoxel_lines3D
            ecs_run(world, line3D_render_system_id, 0, NULL);
        #endif
    }
    if (render2D_update_pipeline == 0) {
        // glDisable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
        shader2D_instance_begin(main_camera_matrix);
        ecs_run(world, ecs_id(InstanceRender2DSystem), 0, NULL);
        shader2D_instance_end();
        ecs_run(world, ecs_id(RenderMaterial2DSystem), 0, NULL);
        // render all ui, layer at a time..
        for (int i = 0; i < max_render_layers; i++) {
            renderer_layer = i;
            ecs_run(world, ecs_id(RenderMeshMaterial2DSystem), 0, NULL);    // render for all tables..
        }
        opengl_unset_mesh();    // for RenderMeshMaterial2DSystem
        opengl_disable_opengl_program();
    }
    // ecs_run(world, ecs_id(Line2DRenderSystem), 0, NULL);
}

void gpu_data_updates() {
    // these get reset first, make them reset during update
    if (mesh_update_pipeline2 == 0) {
        ecs_run(world, ecs_id(MeshUpdateSystem), 0, NULL);
        ecs_run(world, ecs_id(Mesh2DUpdateSystem), 0, NULL);
        ecs_run(world, ecs_id(MeshUvsUpdateSystem), 0, NULL);
        ecs_run(world, ecs_id(Mesh2DUvsUpdateSystem), 0, NULL);
        ecs_run(world, ecs_id(MeshColorsUpdateSystem), 0, NULL);
    }
    ecs_run(world, texture_update_system_id, 0, NULL);
    ecs_run(world, element_mesh_system_id, 0, NULL);
}

void render_loop() {
    #ifdef zoxel_time_render_loop
        begin_timing_absolute()
    #endif
    #ifdef zoxel_cameras
        if (ecs_is_valid(world, ui_cameras[0])) {
            ui_camera_matrix = ecs_get(world, ui_cameras[0], ViewMatrix)->value;
        }
        for (int i = 0; i < main_cameras_count; i++) {
            ecs_entity_t camera = main_cameras[i];
            if (ecs_is_valid(world, camera)) {
                render_camera(world, ecs_get(world, camera, ViewMatrix)->value,
                    ecs_get(world, camera, ScreenPosition)->value, ecs_get(world, camera, ScreenDimensions)->value);
            }
        }
    #endif
    finish_opengl_rendering(world);
    gpu_data_updates();
    #ifdef zoxel_time_render_loop
        end_timing_absolute("    - render_loop")
    #endif
}

// timing the render loop
/*#ifdef zoxel_time_render_loop
#include <time.h>
const double min_render_loop_timing = 0;    // set to higher to check for spikes
#endif*/

// clock_t t = clock();
/*t = clock() - t;
double t2 =  (((double) 1000.0 * t) / CLOCKS_PER_SEC);
if (t2 >= min_render_loop_timing) {
    zoxel_log("Render Time [%fms]\n", t2);
}*/