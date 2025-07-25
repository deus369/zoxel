

void process_terminal_sdl(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--opengles") == 0) {
            opengl_mode = zox_opengl_es;
            zox_log("+ opengl_mode -> [opengl_es]")
        } else if (strcmp(args[i], "--openglcore") == 0) {
            opengl_mode = zox_opengl_core;
            zox_log("+ opengl_mode -> [opengl_core]")
        } else if (strcmp(args[i], "--logsdl") == 0) {
            is_log_sdl = 1;
            zox_log("setting enabled [logsdl]")
        }
    }
}