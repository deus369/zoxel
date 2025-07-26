#define zox_system_ctx(id_, phase, ctx_, ...)\
    zox_system_internal(id_, phase, 1, ctx_, __VA_ARGS__)

#define zox_system_ctx_1(id_, phase, ctx_, ...)\
    zox_system_internal(id_, phase, 0, ctx_, __VA_ARGS__)

#ifdef zox_flecs_4

    #define zox_filter(name, ...)\
        ecs_query_t *name = ecs_query_init(world, &(ecs_query_desc_t) {\
            .expr = #__VA_ARGS__\
        });

    #define zox_change_check();

        /*if (!it->ctx || !ecs_query_changed(it->ctx)) {\
            return;\
        }*/

    #define zox_skip()\
        ecs_iter_skip(it);

    #define zox_skip_if_unchanged(component_index) {\
        if (!ecs_field_is_set(it, component_index)) {\
            zox_skip()\
        }\
    }

#else

    #define zox_filter(name, ...)\
        ecs_query_t *name = ecs_query_init(world, &(ecs_query_desc_t) {\
            .filter.expr = #__VA_ARGS__\
        });

    #define zox_change_check()\
        if (!it->ctx || !ecs_query_changed(it->ctx, NULL)) {\
            return;\
        }

    #define zox_skip()\
        ecs_query_skip(it);

    #define zox_skip_if_unchanged(component_index) {\
        if (!ecs_field_is_set(it, component_index)) {\
            zox_skip()\
        }\
    }

#endif
