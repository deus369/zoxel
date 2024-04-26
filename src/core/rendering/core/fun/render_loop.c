const unsigned char max_render_layers = 32;
int_array_d* render3D_systems;
int_array_d* render2D_systems;
unsigned char renderer_layer;
ecs_entity_t renderer_camera;
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

void render_ui_camera(ecs_world_t *world, const ecs_entity_t e) {
    // remember to check renderer_layer in each 2D  render system
    if (!zox_valid(e)) return; // todo: check if ui is within canvas/view of that camera
    const int2 screen_position = zox_get_value(e, ScreenPosition)
    const int2 screen_dimensions = zox_get_value(e, ScreenDimensions)
    const unsigned char camera_fov = zox_get_value(e, FieldOfView)
    renderer_camera = e;
    render_camera_fov = camera_fov;
    render_camera_matrix = zox_get_value(e, ViewMatrix)
    if (is_using_vulkan) {
#ifdef zox_include_vulkan
        // render ui cameras for vulkan
#endif
    } else {
        glViewport(screen_position.x, screen_position.y, screen_dimensions.x, screen_dimensions.y);
        for (renderer_layer = 0; renderer_layer < max_render_layers; renderer_layer++) {
            for (int j = 0; j < render2D_systems->size; j++)
                ecs_run(world, render2D_systems->data[j], 0, NULL);
        }
    }
}

// This renders all render systems per camera, by externally setting the camera matrix this will be uploaded to all materials
void render_camera(ecs_world_t *world, const ecs_entity_t e) {
    if (!zox_valid(e)) return;
    const float4x4 view_matrix = zox_get_value(e, ViewMatrix)
    const unsigned char camera_fov = zox_get_value(e, FieldOfView)
    const int2 screen_position = zox_get_value(e, ScreenPosition)
    const int2 screen_dimensions = zox_get_value(e, ScreenDimensions)
    renderer_camera = e;
    render_camera_matrix = view_matrix;
    render_camera_fov = camera_fov;
    if (is_using_vulkan) {
#ifdef zox_include_vulkan
        // render cameras for vulkan
#endif
    } else {
        glViewport(screen_position.x, screen_position.y, screen_dimensions.x, screen_dimensions.y);
        for (int i = 0; i < render3D_systems->size; i++)
            ecs_run(world, render3D_systems->data[i], 0, NULL);
        glClear(GL_DEPTH_BUFFER_BIT);
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
        render_camera(world, main_cameras[i]);
    }
    for (int i = 0; i < main_cameras_count; i++) {
        render_ui_camera(world, ui_cameras[i]);
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
