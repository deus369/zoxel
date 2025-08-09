#define zox_pip_resets EcsPostUpdate
// general states
#define zox_general_state_none 0
#define zox_general_state_trigger 1
#define zox_general_state_dirty 2
#define zox_general_state_end 3

#define zox_set_system(system_name, component_name, t, v)\
void system_name(ecs_iter_t *it) {\
    zox_sys_begin()\
    zox_sys_out(component_name)\
    for (int i = 0; i < it->count; i++) {\
        zox_sys_o(component_name, component)\
        if (component->value == t) component->value = v;\
    }\
} zoxd_system(system_name)

#define zox_reset_system(component_name) zox_set_system(component_name##ResetSystem, component_name, 1, 0)

// This needs to update before EcsPreStore as that's when chunks terrain spawn
#define zox_define_reset_system_pip(component_name, pip) zox_system(component_name##ResetSystem, pip, [out] component_name)

#define zox_define_reset_system(component_name) zox_define_reset_system_pip(component_name, zox_pip_resets)

#define zox_define_reset_system_pip2(system_name, component_name, pip) zox_system(system_name, pip, [out] component_name)


// create systems that call function when state hits


#define zox_define_system_state_event(system_name, pip, component, ...)\
    zox_system(system_name##StateEventSystem, pip, [in] component, __VA_ARGS__)

#define zox_define_system_state_event_1(system_name, pip, component, ...)\
    zox_system_1(system_name##StateEventSystem, pip, [in] component, __VA_ARGS__)

#define zox_declare_system_state_event(system_name, component, target, function)\
void system_name##StateEventSystem(ecs_iter_t *it) {\
    zox_sys_world()\
    zox_sys_begin()\
    zox_sys_in(component)\
    for (int i = 0; i < it->count; i++) {\
        zox_sys_e()\
        zox_sys_i(component, comp)\
        if (comp->value == target) {\
            function(world, e);\
        }\
    }\
} zoxd_system(system_name##StateEventSystem)
