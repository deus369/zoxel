int_array_d* gpu_dispose_systems;
int_array_d* gpu_restore_systems;

void initialize_gpu_systems() {
    gpu_dispose_systems = create_int_array_d(initial_dynamic_array_size);
    gpu_restore_systems = create_int_array_d(initial_dynamic_array_size);
}

void dispose_gpu_systems() {
    dispose_int_array_d(gpu_dispose_systems);
    dispose_int_array_d(gpu_restore_systems);
}

void add_to_gpu_dispose_systems(long int id) {
    add_to_int_array_d(gpu_dispose_systems, id);
}

void add_to_gpu_restore_systems(long int id) {
    add_to_int_array_d(gpu_restore_systems, id);
}

void run_gpu_dispose_systems(ecs_world_t *world) {
    for (int i = 0; i < gpu_dispose_systems->size; i++) ecs_run(world, gpu_dispose_systems->data[i], 0, NULL);
}

void run_gpu_restore_systems(ecs_world_t *world) {
    for (int i = 0; i < gpu_restore_systems->size; i++) ecs_run(world, gpu_restore_systems->data[i], 0, NULL);
}

void opengl_dispose_resources(ecs_world_t *world) {
    if (is_using_vulkan) return;
    // zox_log(" > disposing all opengl resources\n");
    rendering = 0;
    minimized = 1; // move this to a system and function for app! when implement multi apps
    updating_time = 0; // timesteps a bit low atm so pause while minimizing
    run_gpu_dispose_systems(world);
}

void opengl_restore_resources(ecs_world_t *world) {
    if (is_using_vulkan) return;
    // zox_log(" > restoring all opengl resources\n");
    run_gpu_restore_systems(world);
    rendering = 1;
    minimized = 0;
    updating_time = 1;
    skip_time_to_current();
}
