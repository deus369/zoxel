const byte max_layers2D = 128; // 64;
int_array_d* render2D_systems;
// todo: add a layer for rendering systems - zox_render3D_system - camera_render_system
int_array_d* render3D_systems;
int_array_d* render3D_plus_systems;

void initialize_render_loop() {
    render2D_systems = create_int_array_d(initial_dynamic_array_size);
    render3D_systems = create_int_array_d(initial_dynamic_array_size);
    render3D_plus_systems = create_int_array_d(initial_dynamic_array_size);
}

void dispose_render_loop() {
    dispose_int_array_d(render2D_systems);
    dispose_int_array_d(render3D_systems);
    dispose_int_array_d(render3D_plus_systems);
}

void add_to_render3D_loop(long int id) {
    add_to_int_array_d(render3D_systems, id);
}

void add_to_render3D_plus_loop(long int id) {
    add_to_int_array_d(render3D_plus_systems, id);
}

void add_to_render2D_loop(long int id) {
    add_to_int_array_d(render2D_systems, id);
}

// #define zoxel_time_render_loop // time our render pass
// todo: instead of using ui_cameras stack, use a system that goes over Cameras
//      if camera has a child camera, run that afterwards
//      you can set a camera to 2D/3D which sets what systems it renders with
