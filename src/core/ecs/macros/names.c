#define zox_get_name(e) ecs_get_name(world, e)
#define zox_set_name(e, name) ecs_set_name(world, e, name);
// #define zox_set_entity_names
// #define zox_debug_spawning

// get these from Text section
// extern void prefab_set_entity_zox_name(ecs_world_t *world, ecs_entity_t e, char label[]);
// extern void set_entity_zox_name(ecs_world_t *world, ecs_entity_t e, char label[]);

char *long_int_itoa(char *str, long int num) {
    if (str == NULL) return NULL;
    sprintf(str, "%lu", num);
    return str;
}

char* get_entity_string(const ecs_entity_t e, const char* name) {
    static char e_string[32];
    long_int_itoa(e_string, (long int) e); // (long int) (rand() % 100000));   //
    int entity_name_length = strlen(name) + 1 + 32 + 1;
    char* entity_name = malloc(entity_name_length);
    for (int i = 0; i < entity_name_length; i++) entity_name[i] = 0;
    strcat(entity_name, name);
    strcat(entity_name, "_");
    strcat(entity_name, e_string);
    return entity_name;
}

void zox_set_entity_name(ecs_world_t *world, const ecs_entity_t e, const char* name) {
    char* name_plus_id = get_entity_string(e, name);
    zox_set_name(e, name_plus_id)
    free(name_plus_id);
}

void zox_debug_spawn(ecs_world_t *world, const ecs_entity_t e, const char* name, const char* entity_type) {
#ifdef zox_set_entity_names
    zox_set_entity_name(world, e, name);
#endif
#ifdef zox_debug_spawning
    zox_log(" + spawned %s [%s] [%lu]\n", entity_type, name, e)
#endif
}

#define zox_prefab_name(label) zox_debug_spawn(world, e, label, "prefab");

#define zox_name(label) zox_debug_spawn(world, e, label, "instance");
