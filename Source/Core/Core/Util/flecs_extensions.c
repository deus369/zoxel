//! My own flecs struct types

// ECS Helper functions
// void ecs_system_enable_multithreading(ecs_world_t *world, long int function)
// {
//     ecs_system_init(world, &(ecs_system_desc_t) { .entity = function, .multi_threaded = 1 } );
// }
// can debug destruction
// printf("Destroying name Memory.\n");

//! A query container for a system.
typedef struct
{
    ecs_query_t *query1;
    ecs_query_t *query2;
} QueryContainer2;