zox_hook(load_shader, (ecs_world_t* world), (world))

void process_shaders(ecs_world_t *world) {
    if (!rendering_initialized) {
        zox_log(" ! rendering is not initialized.\n")
        exit(1);
        return;
    }
    run_hook_load_shader(world);
}

byte get_new_shader_source_index() {
    shaders_count++;
    return shaders_count - 1;
}