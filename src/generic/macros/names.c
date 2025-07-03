#define zox_set_zext_component(e, name, text) zox_set(e, name, { strlen(text), convert_string_to_zext(text) })

// #define zox_debug_spawning
// extern void set_new_zox_name(ecs_world_t *world, const ecs_entity_t e, const char* text);

char *long_int_itoa(char *str, long int num) {
    if (str == NULL) return NULL;
    sprintf(str, "%lu", num);
    return str;
}

#define e_string_length 64
char* get_entity_string(const ecs_entity_t e, const char* name) {
    static char e_string[e_string_length];
    long_int_itoa(e_string, (long int) e); // (long int) (rand() % 100000));   //
    int entity_name_length = strlen(name) + 1 + e_string_length + 1;
    char* entity_name = malloc(entity_name_length);
    for (int i = 0; i < entity_name_length; i++) entity_name[i] = 0;
    strcat(entity_name, name);
    strcat(entity_name, "_");
    strcat(entity_name, e_string);
    return entity_name;
}

void zox_set_entity_name(ecs_world_t *world, const ecs_entity_t e, const char* name) {
    if (!e) {
        return;
    }
    char* name_plus_id = get_entity_string(e, name);
    zox_set_name(e, name_plus_id)
    // zox_set_zext_component(e, ZoxName, name)
    // set_new_zox_name(world, e, name);
    // zox_set(e, ZoxName, { strlen(name), convert_string_to_zext(name) })
    free(name_plus_id);
}

void zox_debug_spawn(ecs_world_t *world, const ecs_entity_t e, const char* name, const char* entity_type) {
#ifdef zox_debug_spawning
    zox_log(" + spawned %s [%s] [%lu] [%s]\n", entity_type, name, e, zox_get_name(e))
#endif
#ifdef zox_set_entity_names
    zox_set_entity_name(world, e, name);
#endif
}

#define zox_prefab_name(label) zox_debug_spawn(world, e, "prefab_"label, "prefab");

#define zox_name(label) zox_debug_spawn(world, e, label, "instance");

#define zox_set_unique_name(e, name) zox_set_entity_name(world, e, name);
