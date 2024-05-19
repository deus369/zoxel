const unsigned char max_layers2D = 64;
unsigned char renderer_layer;
ecs_entity_t renderer_camera;
float4x4 render_camera_matrix;
unsigned char render_camera_fov;
int_array_d* render3D_systems;
int_array_d* render2D_systems;
// #define zoxel_time_render_loop // time our render pass
// todo: instead of using ui_cameras stack, use a system that goes over Cameras
//      if camera has a child camera, run that afterwards
//      you can set a camera to 2D/3D which sets what systems it renders with

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

void clear_viewport() {
    if (is_using_vulkan) {
#ifdef zox_include_vulkan
        vulkan_clear_viewport(viewport_clear_color);
#endif
    } else opengl_clear(viewport_clear_color);
}

void run_rendering() {
    finish_opengl_rendering(world);
}

void camera_render_update(ecs_iter_t *it, const unsigned char is_camera2D) {
    unsigned char do_renders = !headless && rendering; // && !is_using_vulkan;
    if (!do_renders) return;
#ifdef zoxel_time_render_loop
    begin_timing_absolute()
#endif
    zox_iter_world()
    zox_field_in(ViewMatrix, viewMatrixs, 1)
    zox_field_in(FieldOfView, fieldOfViews, 2)
    zox_field_in(ScreenPosition, screenPositions, 3)
    zox_field_in(ScreenDimensions, screenDimensionss, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i_in(ScreenPosition, screenPositions, screenPosition)
        zox_field_i_in(ScreenDimensions, screenDimensionss, screenDimensions)
        zox_field_i_in(ViewMatrix, viewMatrixs, viewMatrix)
        zox_field_i_in(FieldOfView, fieldOfViews, fieldOfView)
        // pass data to systems
        renderer_camera = e;
        render_camera_fov = fieldOfView->value;
        render_camera_matrix = viewMatrix->value;
        if (!is_using_vulkan) glViewport(screenPosition->value.x, screenPosition->value.y, screenDimensions->value.x, screenDimensions->value.y);
#ifdef zox_include_vulkan
        // else { set vulkan viewport; }
#endif
        if (!is_camera2D) {
            for (int j = 0; j < render3D_systems->size; j++) ecs_run(world, render3D_systems->data[j], 0, NULL);
        } else {
            // ui is rendered in layers
            for (renderer_layer = 0; renderer_layer < max_layers2D; renderer_layer++) {
                for (int j = 0; j < render2D_systems->size; j++) ecs_run(world, render2D_systems->data[j], 0, NULL);
            }
        }
    }
    if (!is_camera2D) glClear(GL_DEPTH_BUFFER_BIT);
#ifdef zoxel_time_render_loop
    end_timing_absolute("    - render_loop")
#endif
}

void CameraRender3DSystem(ecs_iter_t *it) {
    camera_render_update(it, 0);
} zox_declare_system(CameraRender3DSystem)

void CameraRenderUISystem(ecs_iter_t *it) {
    camera_render_update(it, 1);
} zox_declare_system(CameraRenderUISystem)
