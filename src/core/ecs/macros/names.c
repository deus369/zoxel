// get these from Text section
extern void prefab_set_entity_zox_name(ecs_world_t *world, ecs_entity_t e, char label[]);
extern void set_entity_zox_name(ecs_world_t *world, ecs_entity_t e, char label[]);

char *long_int_itoa(char *str, long int num) {
    if (str == NULL) return NULL;
    sprintf(str, "%lu", num);
    return str;
}

char* get_entity_string(char label[], ecs_entity_t e) {
    static char e_string[22];
    long_int_itoa(e_string, (long int) e); // (long int) (rand() % 100000));   //
    int entity_name_length = strlen(label) + 1 + 22 + 1;
    char* entity_name = malloc(entity_name_length);
    for (int i = 0; i < entity_name_length; i++) entity_name[i] = 0;
    strcat(entity_name, label);
    strcat(entity_name, "_");
    strcat(entity_name, e_string);
    return entity_name;
}

void set_unique_entity_name(ecs_world_t *world, ecs_entity_t e, char label[]) {
#ifdef zox_profile_entity_names
    char* entity_name = get_entity_string(label, e);
    ecs_set_name(world, e, entity_name);
    free(entity_name);
#endif
}

void zox_debug_prefab(const char* name, ecs_entity_t e) {
#ifdef zox_debug_prefab_spawning
    zox_log(" + spawned prefab [%s] [%lu]\n", name, e)
#endif
}

void zox_debug_instance(const char* name, ecs_entity_t e) {
#ifdef zox_debug_instance_spawning
    zox_log(" + spawned instance [%s] [%lu]\n", name, e)
#endif
}

#define zox_prefab_name(label)\
    prefab_set_entity_zox_name(world, e, label);\
    zox_debug_prefab(label, e);

#define zox_name(label)\
    set_entity_zox_name(world, e, label);\
    zox_debug_instance(label, e);
