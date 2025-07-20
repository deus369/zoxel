void process_arguments_rendering(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "-e") == 0 || strcmp(args[i], "--opengles") == 0) {
            override_opengl_es = 1;
        } else if (strcmp(args[i], "-v") == 0 || strcmp(args[i], "--vulkan") == 0) {
            render_backend = zox_render_backend_vulkan;
        }
    }
}