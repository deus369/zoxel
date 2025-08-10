#define zoxc_custom(name)\
    ECS_COMPONENT_DECLARE(name)

#define zoxc(name, type)\
    typedef struct {\
        type value;\
    } name;\
    zoxc_custom(name)

#define zox_define_component(name)\
    ECS_COMPONENT_DEFINE(world, name);\
    zox_statistics_components++;

#define zox_event_type(name, return_type, ...)\
    typedef struct {\
        return_type (*value)(__VA_ARGS__);\
    } name;

#define zoxc_function(name, return_type, ...)\
    typedef struct {\
        return_type (*value)(__VA_ARGS__);\
    } name;\
    zoxc_custom(name)

#define zox_define_component_w_dest(name)\
    zox_define_component(name)\
    ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });

#define zox_define_destruction(name)\
    ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });

#define zox_define_entity_parent_component2(name, ...)\
    zox_define_component(name)\
    zox_observe(on_destroyed##_##name, EcsOnRemove, __VA_ARGS__)

#define zox_define_entity_parent_component(name) \
    zox_define_entity_parent_component2(name, [out] name)

#define zox_debug_component(T)\
    zox_log(" + component [%s] > [%s]\n", #T, zox_get_name(T));
