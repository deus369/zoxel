#ifdef zox_flecs_4

    #define zox_filter(name, ...)\
        ecs_query_t *name = ecs_query_init(world, &(ecs_query_desc_t) {\
            .expr = #__VA_ARGS__\
        });

    #define zox_system_ctx(id_, phase, ctx_, ...) {\
        ecs_system_desc_t desc = {0}; \
        ecs_entity_desc_t edesc = {0}; \
        ecs_id_t add_ids[3] = {\
            ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0), \
            (phase), \
            0 \
        };\
        edesc.id = ecs_id(id_);\
        edesc.name = #id_;\
        edesc.add = add_ids;\
        desc.entity = ecs_entity_init(world, &edesc);\
        desc.query.expr = #__VA_ARGS__; \
        desc.callback = id_; \
        desc.multi_threaded = 1;\
        desc.ctx = ctx_; \
        ecs_id(id_) = ecs_system_init(world, &desc); \
    }

    #define zox_system_ctx_1(id_, phase, ctx_, ...) {\
        ecs_system_desc_t desc = {0}; \
        ecs_entity_desc_t edesc = {0}; \
        ecs_id_t add_ids[3] = {\
            ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0), \
            (phase), \
            0 \
        };\
        edesc.id = ecs_id(id_);\
        edesc.name = #id_;\
        edesc.add = add_ids;\
        desc.entity = ecs_entity_init(world, &edesc);\
        desc.query.expr = #__VA_ARGS__; \
        desc.callback = id_; \
        desc.multi_threaded = 0;\
        desc.ctx = ctx_; \
        ecs_id(id_) = ecs_system_init(world, &desc); \
    }

    #define zox_change_check()\
        if (!it->ctx || !ecs_query_changed(it->ctx)) {\
            return;\
        }

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

    #define zox_system_ctx(id_, phase, ctx_, ...) {\
        ecs_system_desc_t desc = {0};\
        ecs_entity_desc_t edesc = {0};\
        edesc.id = ecs_id(id_);\
        edesc.name = #id_;\
        edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0);\
        edesc.add[1] = (phase);\
        desc.entity = ecs_entity_init(world, &edesc);\
        desc.query.filter.expr = #__VA_ARGS__; \
        desc.callback = id_;\
        desc.multi_threaded = 1;\
        desc.ctx = ctx_; \
        ecs_id(id_) = ecs_system_init(world, &desc);\
    }

    #define zox_system_ctx_1(id_, phase, ctx_, ...) {\
        ecs_system_desc_t desc = {0};\
        ecs_entity_desc_t edesc = {0};\
        edesc.id = ecs_id(id_);\
        edesc.name = #id_;\
        edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0);\
        edesc.add[1] = (phase);\
        desc.entity = ecs_entity_init(world, &edesc);\
        desc.query.filter.expr = #__VA_ARGS__;\
        desc.callback = id_;\
        desc.ctx = ctx_;\
        ecs_id(id_) = ecs_system_init(world, &desc);\
    }

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
