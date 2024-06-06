zox_event_type(funfun, void, ecs_world_t*)
zoxel_dynamic_array(funfun)
funfun_array_d* load_shader_functions;

void initialize_shader_loading() {
    load_shader_functions = create_funfun_array_d(initial_dynamic_array_size);
}

void dispose_shader_loading() {
    dispose_funfun_array_d(load_shader_functions);
}

void add_load_shader_function(void (*event)(ecs_world_t *)) { // } void (*)(ecs_world_t *) event) { // funfun event) {
    funfun fun_event = (funfun) { event };
    if (!headless) add_to_funfun_array_d(load_shader_functions, fun_event);
}

void run_load_shader_function(ecs_world_t *world, int i) {
    if (load_shader_functions->data[i].value != NULL) (*load_shader_functions->data[i].value)(world);
}

void load_shaders(ecs_world_t *world) {
    for (int i = 0; i < load_shader_functions->size; i++) run_load_shader_function(world, i);
}

unsigned char get_new_shader_source_index() {
    shaders_count++;
    return shaders_count - 1;
}
