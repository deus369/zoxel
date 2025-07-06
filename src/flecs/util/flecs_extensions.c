int zox_count_entities(const ecs_world_t *world, ecs_entity_t id) {
    ecs_iter_t it = ecs_term_iter(world, &(ecs_term_t) { 
         .id = id,
         .src.flags = EcsSelf | EcsUp
    });
    return ecs_iter_count(&it);
}

// int32_t
// ecs_check(world != NULL, ECS_INVALID_PARAMETER, NULL);
// if (!id) return 0;
//error:
//return 0;

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
