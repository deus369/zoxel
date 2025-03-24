#define zox_entities_component(name)\
zox_memory_component(name, ecs_entity_t)\
\
void on_destroyed_##name(ecs_iter_t *it) {\
    zox_field_world()\
    zox_field_in(name, components, 1)\
    for (int i = 0; i < it->count; i++) {\
        zox_field_i(name, components, component)\
        if (!component->value) continue;\
        for (int j = 0; j < component->length; j++) {\
            /*if (zox_valid(component->value[j])) zox_log(" - deleting character [%lu]\n", component->value[j])*/\
            /*zox_delete(component->value[j])*/\
            zox_delete_safe(component->value[j])\
        }\
    }\
}\
\
void remove_index_from_##name(name *component, const int i) {\
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
byte remove_from_##name(name *component, const ecs_entity_t data) {\
    if (!component || !component->value) return 0;\
    for (int i = 0; i < component->length; i++) {\
        if (component->value[i] == data) {\
            remove_index_from_##name(component, i);\
            return 1;\
        }\
    }\
    return 0;\
}\
\
byte is_in_##name(name *component, const ecs_entity_t data) {\
    if (!component->value) return 0;\
        for (int i = 0; i < component->length; i++)\
            if (component->value[i] == data) return 1;\
    return 0;\
}\
\
byte add_unique_to_##name(name *component, const ecs_entity_t data) {\
    if (!is_in_##name(component, data)) return add_to_##name(component, data);\
    else return 0;\
}

#define zox_define_entities_component2(name, ...)\
zox_define_memory_component(name)\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed_##name,\
    .events = { EcsOnRemove },\
});

#define zox_define_entities_component(name) zox_define_entities_component2(name, [in] name)
