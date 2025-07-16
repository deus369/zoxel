void process_arguments_sounds(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        // zox_log("- arg %i [%s]", i, args[i])
        if (strcmp(args[i], "--nosound") == 0 || strcmp(args[i], "--nosounds") == 0) {
            nosounds = 1;
            zox_log("+ setting enabled [nosounds]")
        }
    }
}