zox_hook(terminal_command, (ecs_world_t* world, char* args[], int count), (world, args, count))

/*terminal_inputs_array_d* terminal_functions;

void dispose_functions_terminal() {
    dispose_terminal_inputs_array_d(terminal_functions);
}

void add_hook_terminal_command(void (*event)(ecs_world_t* world, char* args[], int count)) {
    add_to_terminal_inputs_array_d(terminal_functions, (terminal_inputs) { event });
}

void initialize_functions_terminal() {
    terminal_functions = create_terminal_inputs_array_d(initial_dynamic_array_size);
    add_hook_terminal_command(process_arguments_help);
}

void process_arguments(ecs_world_t *world, char* args[], int count) {
    for (int i = 0; i < terminal_functions->size; i++) {
        if (terminal_functions->data[i].value != NULL) {
            (*terminal_functions->data[i].value)(world, args, count);
        }
    }
}*/