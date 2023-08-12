// \todo Create a queue of 3D models to render, including materials, etc
//  - each type of render queue has different data based on the shaders
//  - inside ecs systems, can run multithread, add things to queues to render
unsigned char renderer_layer;
extern long int render_terrain_chunks_system_id;
extern long int line3D_render_system_id;
extern long int cube_lines_render_system_id;

void render_pre_loop() {
    opengl_clear();             // cannot just clear in a view port with opengl?
}

//! This renders all render systems per camera, by externally setting the camera matrix this will be uploaded to all materials.
void render_camera(ecs_world_t *world, float4x4 camera_matrix, int2 position, int2 size) {
    render_camera_matrix = camera_matrix;
    // if (check_opengl_error("[pre glViewport Error]")) return;
    glViewport(position.x, position.y, size.x, size.y);
    // opengl_instance3D_begin(render_camera_matrix);
    if (render3D_update_pipeline == 0) {
        // ecs_run(world, ecs_id(InstanceRender3DSystem), 0, NULL);
        // opengl_disable_opengl_program();
        ecs_run(world, ecs_id(Render3DSystem), 0, NULL);    // skybox
        ecs_run(world, render_terrain_chunks_system_id, 0, NULL);
        ecs_run(world, ecs_id(RenderCharacters3DSystem), 0, NULL);
        ecs_run(world, ecs_id(Render3DTexturedSystem), 0, NULL);    // statbars
        ecs_run(world, line3D_render_system_id, 0, NULL);
        ecs_run(world, cube_lines_render_system_id, 0, NULL);
    }
    if (render2D_update_pipeline == 0) {
        // glDisable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
        render_ui_in_layers(world);
        /*shader2D_instance_begin(render_camera_matrix);
        ecs_run(world, ecs_id(InstanceRender2DSystem), 0, NULL);
        shader2D_instance_end();
        ecs_run(world, ecs_id(RenderMaterial2DSystem), 0, NULL);*/
        // ecs_run(world, ecs_id(RenderMaterial2DSystem2), 0, NULL);
    }
    // ecs_run(world, ecs_id(Line2DRenderSystem), 0, NULL);
    // check_opengl_error("render_camera");
    // check_opengl_error("[render_camera]");
}

void render_loop() {
    #ifdef zoxel_time_render_loop
        begin_timing_absolute()
    #endif
    #ifdef zoxel_cameras
        if (ecs_is_valid(world, ui_cameras[0])) ui_camera_matrix = ecs_get(world, ui_cameras[0], ViewMatrix)->value;
        for (int i = 0; i < main_cameras_count; i++) {
            ecs_entity_t camera = main_cameras[i];
            if (!ecs_is_valid(world, camera)) continue;
            render_camera(world, ecs_get(world, camera, ViewMatrix)->value, ecs_get(world, camera, ScreenPosition)->value, ecs_get(world, camera, ScreenDimensions)->value);
        }
    #endif
    finish_opengl_rendering(world);
    #ifdef zoxel_time_render_loop
        end_timing_absolute("    - render_loop")
    #endif
}