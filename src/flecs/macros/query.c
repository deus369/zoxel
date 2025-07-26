#define zox_sys_query()\
    ecs_query_t *query = it->ctx;\
    if (!query) {\
        return;\
    }

#define zox_sys_query_begin()\
    ecs_iter_t it2 = ecs_query_iter(world, query);

#define zox_sys_query_loop()\
    ecs_query_next(&it2)

// #define zox_sys_query_end() ;


#ifdef zox_flecs_4

    #define zox_sys_query_end() ;

#else

    #define zox_sys_query_end()\
        ecs_iter_fini(&it2);

#endif
