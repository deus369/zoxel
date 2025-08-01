#define zox_memory_component_with_remove(T, type)\
    zox_memory_component(T, type)\
    zox_memory_component_removes(T, type)

#define zox_entities_component(T)\
\
zox_memory_component_with_remove(T, ecs_entity_t)\
\
void dispose2_##T(ecs_world_t *world, const T *component) {\
    if (!component->value || !component->length) {\
        return;\
    }\
    for (int j = 0; j < component->length; j++) {\
        zox_delete_safe(component->value[j])\
    }\
}\
\
void on_destroyed_##T(ecs_iter_t *it) {\
    zox_sys_world()\
    zox_sys_begin()\
    zox_sys_in(T)\
    for (int i = 0; i < it->count; i++) {\
        zox_sys_i(T, component)\
        if (component->value) {\
            dispose2_##T(world, component);\
        }\
    }\
}\
\
byte is_in_##T(T *component, const ecs_entity_t data) {\
    if (!component || !component->value) {\
        return 0;\
    }\
    for (int i = 0; i < component->length; i++) {\
        if (component->value[i] == data) {\
            return 1;\
        }\
    }\
    return 0;\
}\
\
byte add_unique_to_##T(T *component, const ecs_entity_t data) {\
    if (!is_in_##T(component, data)) {\
        return add_to_##T(component, data);\
    } else {\
        return 0;\
    }\
}

#define zox_define_entities_component(T)\
    zox_define_memory_component(T)\
    zox_observe(on_destroyed_##T, EcsOnRemove, [in] T)
