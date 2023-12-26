zox_event_type(funfun, void, ecs_world_t*)
zoxel_dynamic_array(funfun)
funfun_array_d* load_shader_functions;
funfun_array_d* restore_shader_functions;

void initialize_shader_loading() {
    load_shader_functions = create_funfun_array_d(initial_dynamic_array_size);
    restore_shader_functions = create_funfun_array_d(initial_dynamic_array_size);
}

void dispose_shader_loading() {
    dispose_funfun_array_d(load_shader_functions);
    dispose_funfun_array_d(restore_shader_functions);
}

void add_load_shader_function(funfun event) {
    if (!headless) add_to_funfun_array_d(load_shader_functions, event);
}

void add_restore_shader_function(funfun event) {
    if (!headless) add_to_funfun_array_d(restore_shader_functions, event);
}

void run_load_shader_function(ecs_world_t *world, int i) {
    if (load_shader_functions->data[i].value != NULL) (*load_shader_functions->data[i].value)(world);
}

void load_shaders_dynamic(ecs_world_t *world) {
    for (int i = 0; i < load_shader_functions->size; i++) run_load_shader_function(world, i);
}

void run_restore_shader_function(ecs_world_t *world, int i) {
    if (restore_shader_functions->data[i].value != NULL) (*restore_shader_functions->data[i].value)(world);
}

void restore_shaders_dynamic(ecs_world_t *world) {
    for (int i = 0; i < restore_shader_functions->size; i++) run_restore_shader_function(world, i);
}
