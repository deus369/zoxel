void on_module_dispose_rendering(ecs_world_t *world, void *ctx) {
    dispose_render_loop();
    dispose_gpu_systems();
    dispose_hook_load_shader();
}