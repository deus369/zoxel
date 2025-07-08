#define zox_entities_component(name)\
    zox_entities_component_debug(name, 0)

#define zox_entities_component_debug(name, is_log)\
zox_memory_component_with_remove_logging(name, ecs_entity_t, is_log)\
\
void dispose2_##name(ecs_world_t *world, const name *component) {\
    if (!component->value || !component->length) {\
        if (is_log) {\
            /*zox_log("- disposing nothing\n")*/\
        }\
        return;\
    }\
    if (is_log) {\
        /*zox_log("- disposing [%i]s\n", component->length)*/\
    }\
    for (int j = 0; j < component->length; j++) {\
        if (is_log) {\
            if (zox_valid(component->value[j])) {\
                zox_log("   - [%lu] [%i of %i]\n", component->value[j], j, component->length)\
            }\
        }\
        zox_delete_safe(component->value[j])\
    }\
}\
\
void on_destroyed_##name(ecs_iter_t *it) {\
    zox_field_world()\
    zox_field_in(name, components, 1)\
    for (int i = 0; i < it->count; i++) {\
        zox_field_i(name, components, component)\
        if (!component->length) {\
            continue;\
        }\
        if (is_log) {\
            zox_field_e()\
            zox_log("- disposing [%s]'s [%s] (%i)\n", zox_get_name(e), #name, component->length)\
        }\
        dispose2_##name(world, component);\
    }\
}\
\
byte is_in_##name(name *component, const ecs_entity_t data) {\
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
byte add_unique_to_##name(name *component, const ecs_entity_t data) {\
    if (!is_in_##name(component, data)) {\
        return add_to_##name(component, data);\
    } else {\
        return 0;\
    }\
}

#define zox_define_entities_component2(name, ...)\
    zox_define_memory_component(name)\
    zox_observe(on_destroyed_##name, EcsOnRemove, __VA_ARGS__)

#define zox_define_entities_component(name)\
    zox_define_entities_component2(name, [in] name)

/*
void remove_index_from_##name(name *component, const int i) {\
    for (int j = i; j < component->length - 1; j++) {\
        component->value[j] = component->value[j + 1];\
    }\
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
    if (!component || !component->value) {\
        return 0;\
    }\
    for (int i = 0; i < component->length; i++) {\
        if (component->value[i] == data) {\
            remove_index_from_##name(component, i);\
            return 1;\
        }\
    }\
    return 0;\
}\
*/
