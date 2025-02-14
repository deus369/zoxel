byte disable_npcs = 0;

void process_arguments_characters(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--nonpc") == 0 || strcmp(args[i], "--nonpcs") == 0) {
            disable_npcs = 1;
        }
    }
    // extra disables
    #if defined(zox_disable_npcs)
        disable_npcs = 1;
    #endif
}