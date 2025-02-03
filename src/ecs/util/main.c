general_fun_array_d* update_functions;

void initialize_update_loop() {
    update_functions = create_general_fun_array_d(initial_dynamic_array_size);
}

void dispose_update_loop() {
    dispose_general_fun_array_d(update_functions);
}

void add_to_update_loop(void (*event)(ecs_world_t *)) {
    general_fun fun_event = (general_fun) { event };
    add_to_general_fun_array_d(update_functions, fun_event);
}

void run_update_loop(ecs_world_t *world) {
    for (int i = 0; i < update_functions->size; i++) {
        if (update_functions->data[i].value != NULL) {
            (*update_functions->data[i].value)(world);
        }
    }
}