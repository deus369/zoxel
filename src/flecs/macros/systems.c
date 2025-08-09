#define zoxd_system(name)\
    ECS_SYSTEM_DECLARE(name);

// until i replace old
#define zoxd_system2(name)\
    ECS_SYSTEM_DECLARE(name)

#if defined(zox_enable_log_new_system) && !defined(zox_disable_logs)
    #define zox_log_new_system(msg, ...) zox_log(msg, ##__VA_ARGS__)
#else
    #define zox_log_new_system(msg, ...) { }
#endif

#ifdef zox_flecs_4

    #define zox_system_internal(id_, phase, multi_threaded_, ctx_, ...) { \
        ecs_entity_desc_t edesc = {0}; \
        ecs_id_t add_ids[3] = {\
            ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0), \
            (phase), \
            0 \
        };\
        edesc.id = ecs_id(id_);\
        edesc.name = #id_;\
        edesc.add = add_ids;\
        ecs_system_desc_t desc = {0}; \
        desc.entity = ecs_entity_init(world, &edesc);\
        desc.query.expr = #__VA_ARGS__; \
        desc.callback = id_; \
        desc.multi_threaded = multi_threaded_;\
        desc.ctx = ctx_;\
        ecs_id(id_) = ecs_system_init(world, &desc); \
        zox_log_new_system("+ new system [%s]", #id_)\
        zox_statistics_systems++;\
    };

#else

    #define zox_system_internal(id_, phase, multi_threaded_, ctx_, ...) { \
        ecs_entity_desc_t edesc = {0}; \
        edesc.id = ecs_id(id_);\
        edesc.name = #id_;\
        edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0);\
        edesc.add[1] = (phase);\
        ecs_system_desc_t desc = {0}; \
        desc.entity = ecs_entity_init(world, &edesc);\
        desc.query.filter.expr = #__VA_ARGS__; \
        desc.callback = id_; \
        desc.multi_threaded = multi_threaded_;\
        desc.ctx = ctx_;\
        ecs_id(id_) = ecs_system_init(world, &desc); \
        zox_log_new_system("+ new system [%s]", #id_)\
        zox_statistics_systems++;\
    };

#endif

#define zox_system(id_, phase, ...)\
    zox_system_internal(id_, phase, 1, 0, __VA_ARGS__)

#define zox_system_1(id_, phase, ...)\
    zox_system_internal(id_, phase, 0, 0, __VA_ARGS__)

#define zox_system_m(id_, multi_threaded_, ...)\
    zox_system_internal(id_, EcsOnUpdate, multi_threaded_, 0, __VA_ARGS__)
