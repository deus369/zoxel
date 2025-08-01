general_fun_array_d* post_update_functions;

void initialize_post_update_loop() {
    post_update_functions = create_general_fun_array_d(initial_dynamic_array_size);
}

void dispose_post_update_loop() {
    dispose_general_fun_array_d(post_update_functions);
}

void add_to_post_update_loop(void (*event)(ecs_world_t *)) {
    general_fun fun_event = (general_fun) { event };
    add_to_general_fun_array_d(post_update_functions, fun_event);
}

void run_post_update_loop(ecs_world_t *world) {
    for (size_t i = 0; i < post_update_functions->size; i++) {
        if (post_update_functions->data[i].value != NULL) {
            (*post_update_functions->data[i].value)(world);
        }
    }
}