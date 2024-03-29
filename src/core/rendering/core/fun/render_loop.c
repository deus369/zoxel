// \todo Create a queue of 3D models to render, including materials, etc
//  - each type of render queue has different data based on the shaders
//  - inside ecs systems, can run multithread, add things to queues to render
// > can i make a viewport an entity, and then run this in a viewport system?!
//      > yes, using the glViewport -> position.x, position.y, size.x, size.y
//          > with render systems as data, camera view data, etc
const unsigned char max_render_layers = 32;
unsigned char renderer_layer;
int_array_d* render3D_systems;
int_array_d* render2D_systems;
// todo: replace this with a render stack, which can easily be used in a camera_render_system
//      > it can also be sorted better for z issues on translucent materials
float4x4 render_camera_matrix;
unsigned char render_camera_fov;

void initialize_render_loop() {
    render2D_systems = create_int_array_d(initial_dynamic_array_size);
    render3D_systems = create_int_array_d(initial_dynamic_array_size);
}

void dispose_render_loop() {
    dispose_int_array_d(render2D_systems);
    dispose_int_array_d(render3D_systems);
}

void add_to_render3D_loop(long int id) {
    add_to_int_array_d(render3D_systems, id);
}

void add_to_render2D_loop(long int id) {
    add_to_int_array_d(render2D_systems, id);
}

// This renders all render systems per camera, by externally setting the camera matrix this will be uploaded to all materials
void render_camera(ecs_world_t *world, const float4x4 camera_matrix, const unsigned char camera_fov, const int2 position, const int2 size) {
    render_camera_matrix = camera_matrix;
    render_camera_fov = camera_fov;
    if (is_using_vulkan) {
#ifdef zox_include_vulkan
        // render cameras for vulkan
#endif
    } else {
        glViewport(position.x, position.y, size.x, size.y);
        for (int i = 0; i < render3D_systems->size; i++) ecs_run(world, render3D_systems->data[i], 0, NULL);
        glClear(GL_DEPTH_BUFFER_BIT);
        // remember to check renderer_layer in each 2D  render system
        if (ecs_is_valid(world, ui_cameras[0])) render_camera_matrix = zox_get_value(ui_cameras[0], ViewMatrix)
        for (renderer_layer = 0; renderer_layer < max_render_layers; renderer_layer++) {
            for (int i = 0; i < render2D_systems->size; i++) ecs_run(world, render2D_systems->data[i], 0, NULL);
        }
    }
}

void render_pre_loop() {
    if (is_using_vulkan) {
#ifdef zox_include_vulkan
        // render cameras for vulkan
        vulkan_clear_viewport(viewport_clear_color);
#endif
    } else opengl_clear(viewport_clear_color);
}

void render_loop(ecs_world_t *world) {
#ifdef zoxel_time_render_loop
    begin_timing_absolute()
#endif
#ifdef zoxel_cameras
    for (int i = 0; i < main_cameras_count; i++) {
        ecs_entity_t camera = main_cameras[i];
        if (!ecs_is_valid(world, camera)) continue;
        const float4x4 view_matrix = zox_get_value(camera, ViewMatrix)
        const unsigned char camera_fov = zox_get_value(camera, FieldOfView)
        const int2 screen_position = zox_get_value(camera, ScreenPosition)
        const int2 screen_dimensions = zox_get_value(camera, ScreenDimensions)
        render_camera(world, view_matrix, camera_fov, screen_position, screen_dimensions);
    }
#endif
    finish_opengl_rendering(world);
#ifdef zoxel_time_render_loop
    end_timing_absolute("    - render_loop")
#endif
}

// opengl_instance3D_begin(render_camera_matrix);
// ecs_run(world, ecs_id(InstanceRender3DSystem), 0, NULL);
// opengl_disable_opengl_program();
/*shader2D_instance_begin(render_camera_matrix);
ecs_run(world, ecs_id(InstanceRender2DSystem), 0, NULL);
shader2D_instance_end();
ecs_run(world, ecs_id(RenderMaterial2DSystem), 0, NULL);*/
// ecs_run(world, ecs_id(RenderMaterial2DSystem2), 0, NULL);
// glDisable(GL_DEPTH_TEST);
