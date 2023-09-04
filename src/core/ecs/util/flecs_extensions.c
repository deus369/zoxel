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
    #ifdef zoxel_entity_names
        char* entity_name = get_entity_string(label, e);
        ecs_set_name(world, e, entity_name);
        free(entity_name);
    #endif
}

// ECS Helper functions
// void ecs_system_enable_multithreading(ecs_world_t *world, long int function)
// {
//     ecs_system_init(world, &(ecs_system_desc_t) { .entity = function, .multi_threaded = 1 } );
// }
// can debug destruction
// printf("Destroying name Memory.\n");

/*int32_t ecs_count_id_with_up(const ecs_world_t *world, ecs_entity_t id) {
    ecs_check(world != NULL, ECS_INVALID_PARAMETER, NULL);
    if (!id) {
        return 0;
    }
    ecs_iter_t it = ecs_term_iter(world, &(ecs_term_t) { 
         .id = id,
         .src.flags = EcsSelf | EcsUp
    });
    return ecs_iter_count(&it);
error:
    return 0;
}*/

//! A query container for a system.
/*typedef struct {
    ecs_query_t *query1;
    ecs_query_t *query2;
} QueryContainer2;*/