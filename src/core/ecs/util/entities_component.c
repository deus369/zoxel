#define zox_entities_component(name)\
zox_memory_component(name, ecs_entity_t)\
void on_destroyed##_##name(ecs_iter_t *it) {\
    zox_iter_world()\
    zox_field_in(name, components, 1)\
    for (int i = 0; i < it->count; i++) {\
        zox_field_i_in(name, components, component)\
        if (!component->value) continue;\
        for (int j = 0; j < component->length; j++) zox_delete(component->value[j]);\
    }\
}\
\
void remove_index_from##_##name(name *component, const int i) {\
    /* shift list down, as we are removing i*/\
    for (int j = i; j < component->length - 1; j++) {\
        component->value[j] = component->value[j + 1];\
    }\
    /* resize list: length = length - 1*/\
    component->length--;\
    if (component->length == 0) {\
        free(component->value);\
        component->value = NULL;\
    } else {\
        component->value = realloc(component->value, component->length * sizeof(ecs_entity_t));\
    }\
}\
\
unsigned char remove_from##_##name(name *component, const ecs_entity_t data) {\
    for (int i = 0; i < component->length; i++) {\
        if (component->value[i] == data) {\
            remove_index_from##_##name(component, i);\
            return 1;\
        }\
    }\
    return 0;\
}\
\
unsigned char is_in##_##name(name *component, const ecs_entity_t data) {\
    if (!component->value) return 0;\
        for (int i = 0; i < component->length; i++)\
            if (component->value[i] == data) return 1;\
    return 0;\
}\
\
unsigned char add_unique_to##_##name(name *component, const ecs_entity_t data) {\
    if (!is_in##_##name(component, data)) return add_to##_##name(component, data);\
    else return 0;\
}

#define zox_define_entities_component2(name, ...)\
zox_define_memory_component(name)\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});

#define zox_define_entities_component(name) zox_define_entities_component2(name, [in] name)


/*
unsigned char add_to##_##name(name *component, const ecs_entity_t data) {\
    if (component->value) {\
        for (int i = 0; i < component->length; i++)\
            if (component->value[i] == data) return 0;\
        component->length++;\
        component->value = realloc(component->value, component->length * sizeof(ecs_entity_t));\
        component->value[component->length - 1] = data;\
    } else {\
        component->length = 1;\
        component->value = malloc(sizeof(ecs_entity_t));\
        component->value[0] = data;\
    }\
    return 1;\
}\
*/
