#define zox_define_increment_system(component, ...)\
    zox_system(component##IncrementSystem, EcsOnLoad, [out] component, __VA_ARGS__)

#define zox_define_increment_system_pip(component, p, ...)\
    zox_system(component##IncrementSystem, p, [out] component, __VA_ARGS__)

#define zox_define_increment_system_external(component, full_path_component, pip, ...)\
    zox_system(component##IncrementSystem, pip, [out] full_path_component, __VA_ARGS__)

// if non zero, moves to target state
#define zox_increment_system(component_name, target)\
void component_name##IncrementSystem(ecs_iter_t *it) {\
    zox_sys_begin()\
    zox_sys_out(component_name)\
    for (int i = 0; i < it->count; i++) {\
        zox_sys_o(component_name, component)\
        if (component->value) {\
            if (component->value < target) {\
                component->value++;\
            }\
        }\
    }\
} zox_declare_system(component_name##IncrementSystem)

// if non zero, moves to target state, then resets
#define zox_increment_system_with_reset(component_name, target)\
void component_name##IncrementSystem(ecs_iter_t *it) {\
    zox_sys_begin()\
    zox_sys_out(component_name)\
    for (int i = 0; i < it->count; i++) {\
        zox_sys_o(component_name, component)\
        if (!component->value) {\
            continue;\
        } else if (component->value == target) {\
            component->value = 0;\
        } else {\
            component->value++;\
        }\
        /*zox_log(" + %lu is incrementing %s [%s - %i]\n", it->entities[i], #component_name, #target, component->value)*/\
    }\
} zox_declare_system(component_name##IncrementSystem)

// if non zero, moves to target state
#define zox_increment_system_with_reset_extra(component_name, first_iterator, first_target, second_iterator, reset_value)\
void component_name##IncrementSystem(ecs_iter_t *it) {\
    zox_sys_begin()\
    zox_sys_out(component_name)\
    for (int i = 0; i < it->count; i++) {\
        zox_sys_o(component_name, component)\
        if (component->value >= first_iterator && component->value < first_target) {\
            component->value++;\
        } else if (component->value >= second_iterator && component->value < reset_value) {\
            component->value++;\
        } else if (component->value == reset_value) {\
            component->value = 0;\
        }\
    }\
} zox_declare_system(component_name##IncrementSystem)
