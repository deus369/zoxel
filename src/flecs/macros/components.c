#define zox_custom_component(name)\
    ECS_COMPONENT_DECLARE(name);

#define zox_component(name, type)\
    typedef struct {\
        type value;\
    } name;\
    zox_custom_component(name)

#define zox_define_component(name)\
    ECS_COMPONENT_DEFINE(world, name);\
    zox_statistics_components++;

#define zox_event_type(name, return_type, ...)\
    typedef struct {\
        return_type (*value)(__VA_ARGS__);\
    } name;

#define zox_function_component(name, return_type, ...)\
    typedef struct {\
        return_type (*value)(__VA_ARGS__);\
    } name;\
    zox_custom_component(name)

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

#define component_id_list(name)\
    ecs_entity_t_array_d* component_ids##_##name;\
    \
    void initialize_component_ids##_##name() {\
        component_ids##_##name = create_ecs_entity_t_array_d(initial_dynamic_array_size);\
    }\
    \
    void dispose_component_ids##_##name() {\
        dispose_ecs_entity_t_array_d(component_ids##_##name);\
    }\
    \
    byte is_component_type##_##name(ecs_entity_t id) {\
        return is_in_ecs_entity_t_array_d(component_ids##_##name, id);\
    }

#define zox_debug_component(name)\
    zox_log(" + component [%s] > [%s]\n", #name, zox_get_name(name))
