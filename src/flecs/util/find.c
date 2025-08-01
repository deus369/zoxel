

#define clear_memory_component(name, component)\
    dispose_##name(component);

#define resize_memory_component(T, component, type, new_length) {\
    if (component->length != new_length) {\
        if (new_length == 0) {\
            clear_memory_component(T, component)\
        } else if (component->value) {\
            type* new_memory = realloc(component->value, new_length * sizeof(type));\
            if (!new_memory) {\
                zox_log_error("Failure with realloc")\
            } else {\
                component->value = new_memory;\
                component->length = new_length;\
            }\
        } else {\
            initialize_##T(component, new_length);\
        }\
    }\
}

#define find_array_component_with_tag2(value, length, tag, e)\
    ecs_entity_t e = 0;\
    for (int i = 0; i < length; i++) {\
        if (zox_has(value[i], tag)) {\
            e = value[i];\
            break;\
        }\
    }

#define find_array_component_with_tag(component, tag, e)\
    ecs_entity_t e = 0;\
    for (int i = 0; i < component->length; i++) {\
        if (zox_has(component->value[i], tag)) {\
            e = component->value[i];\
            break;\
        }\
    }

#define find_array_component_with_tag_id(component, tag_id, name)\
    ecs_entity_t name = 0;\
    for (int i = 0; i < component->length; i++) {\
        if (zox_has_id(component->value[i], tag_id)) {\
            name = component->value[i];\
            break;\
        }\
    }



#define zox_memory_component_removes(T, type)\
    \
    byte remove_at_##T(T *component, int index) {\
        if (!component->value || index < 0 || index >= component->length) {\
            return 0;\
        }\
        for (int i = index; i < component->length - 1; i++) {\
            component->value[i] = component->value[i + 1];\
        }\
        component->length--;\
        if (!component->length) {\
            free(component->value);\
            component->value = NULL;\
        } else {\
            component->value = realloc(component->value, component->length * sizeof(type));\
        }\
        return 1;\
    }\
    \
    byte remove_from_##T(T *component, const type data) {\
        byte success = 0;\
        for (int i = 0; i < component->length; i++) {\
            if (component->value[i] == data) {\
                success = remove_at_##T(component, i);\
                break;\
            }\
        }\
        return success;\
    }
