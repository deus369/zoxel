byte disable_npcs = 0;
byte disable_npc_movement = 0;
ulong zox_stats_characters = 0;
byte is_characters_instanced = 0;

void process_arguments_characters(ecs_world_t *world, char* args[], int count) {
    (void) world;
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--nonpc") == 0 || strcmp(args[i], "--nonpcs") == 0) {
            disable_npcs = 1;
        }
    }
}