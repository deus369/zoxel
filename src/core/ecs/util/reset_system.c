#define zox_pip_resets EcsPostUpdate

#define zox_increment_system(component_name, target)\
void component_name##IncrementSystem(ecs_iter_t *it) {\
    zox_field_out(component_name, components, 1)\
    for (int i = 0; i < it->count; i++) {\
        zox_field_i_out(component_name, components, component)\
        if (!component->value) continue;\
        else if (component->value == target) component->value = 0;\
        else component->value++;\
    }\
} zox_declare_system(component_name##IncrementSystem)

#define zox_define_increment_system(component, pip) zox_system(component##IncrementSystem, pip, [out] component)

#define zox_set_system(system_name, component_name, t, v)\
void system_name(ecs_iter_t *it) {\
    zox_field_out(component_name, components, 1)\
    for (int i = 0; i < it->count; i++) {\
        zox_field_i_out(component_name, components, component)\
        if (component->value == t) component->value = v;\
    }\
} zox_declare_system(system_name)

#define zox_reset_system(component_name) zox_set_system(component_name##ResetSystem, component_name, 1, 0)

// This needs to update before EcsPreStore as that's when chunks terrain spawn
#define zox_define_reset_system_pip(component_name, pip) zox_system(component_name##ResetSystem, pip, [out] component_name)

#define zox_define_reset_system(component_name) zox_define_reset_system_pip(component_name, zox_pip_resets)

#define zox_define_reset_system_pip2(system_name, component_name, pip) zox_system(system_name, pip, [out] component_name)


