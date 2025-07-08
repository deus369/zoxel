int total_memorys_allocated = 0;

#define zox_memory_component(name, type)\
    zox_memory_component_logging(name, type, 0)

#define zox_define_memory_component(name)\
    zox_define_memory_component2(name, [out] name)

#define zox_memory_component_with_remove(name, type)\
    zox_memory_component(name, type)\
    zox_memory_component_removes(name, type)

#define zox_memory_component_with_remove_logging(name, type, is_log)\
    zox_memory_component_logging(name, type, is_log)\
    zox_memory_component_removes(name, type)

// assumes non zero
#define initialize_memory_component(name, component, type, new_length) {\
    const int memory_length = new_length * sizeof(type);\
    if (memory_length > 0) {\
        type *new_memory = malloc(memory_length);\
        if (!new_memory) {\
            zox_log(" ! failed (init) allocating memory in clone_" #name " [%i]\n", memory_length)\
            component->value = NULL;\
            component->length = 0;\
        } else {\
            component->value = new_memory;\
            component->length = new_length;\
            total_memorys_allocated++;\
            name##_memorys_allocated++;\
        }\
    } else {\
        if (memory_length < 0) {\
            zox_log(" ! cannot allocate memory in clone_" #name " [%i]\n", memory_length)\
        }\
        component->value = NULL;\
        component->length = 0;\
    }\
}

#define zox_memory_component_logging(name, type, is_log)\
int name##_memorys_allocated = 0;\
typedef struct {\
    int length;\
    type *value;\
    pthread_rwlock_t lock;\
} name;\
zox_custom_component(name)\
\
void dispose_##name(name *component) {\
    if (!component->value) {\
        return;\
    }\
    pthread_rwlock_wrlock(&component->lock);\
    free(component->value);\
    component->value = NULL;\
    component->length = 0;\
    pthread_rwlock_unlock(&component->lock);\
    pthread_rwlock_destroy(&component->lock);\
    name##_memorys_allocated--;\
    total_memorys_allocated--;\
    /*zox_log(" [%s] disposing of entity with memory component\n", #name)*/\
}\
\
void clone_##name(name* dst, const name* src) {\
    if (!src->value) {\
        dispose_##name(dst);\
    } else {\
        int memory_length = src->length * sizeof(type);\
        type *new_memory = malloc(memory_length);\
        if (!new_memory) {\
            zox_log("! failed allocating memory in clone_" #name "\n")\
            return;\
        }\
        if (dst->value) {\
            dispose_##name(dst);\
        }\
        memcpy(new_memory, src->value, memory_length);\
        dst->value = new_memory;\
        dst->length = src->length;\
        total_memorys_allocated++;\
        name##_memorys_allocated++;\
    }\
}\
\
void name##_dtor(void *ptr, int32_t count, const ecs_type_info_t *info) {\
    name *data = ptr;\
    for (int i = 0; i < count; i++) {\
        if (data[i].value) {\
            free(data[i].value);\
            data[i].value = NULL;\
        }\
    }\
}\
\
void name##_move(void *dst_ptr, void *src_ptr, int32_t count, const ecs_type_info_t *info) {\
    name *dst = dst_ptr;\
    name *src = src_ptr;\
    for (int i = 0; i < count; i++) {\
        dst[i].value = src[i].value;\
        dst[i].length = src[i].length;\
        src[i].value = NULL;\
        src[i].length = 0;\
    }\
}\
\
void name##_ctor(void *ptr, int32_t count, const ecs_type_info_t *info) {\
    name *data = ptr;\
    for (int i = 0; i < count; i++) {\
        data[i] = (name) {\
            .length = 0,\
            .value = NULL\
        };\
        pthread_rwlock_init(&data[i].lock, NULL);\
    }\
}\
\
void name##_copy(void *dst_ptr, const void *src_ptr, int32_t count, const ecs_type_info_t *info) {\
    name *dst = dst_ptr;\
    const name *src = src_ptr;\
    for (int i = 0; i < count; i++) {\
        if (src[i].value && src[i].length > 0) {\
            dst[i].value = malloc(src[i].length * sizeof(type));\
            if (!dst[i].value) {\
                dst[i].length = 0;\
                fprintf(stderr, "Copy: "#name" Failed to allocate memory\n");\
            } else {\
                dst[i].length = src[i].length;\
                memcpy(dst[i].value, src[i].value, src[i].length * sizeof(type));\
            }\
        } else {\
            dst[i].length = 0;\
            dst[i].value = NULL;\
        }\
    }\
}\
\
byte add_to_##name(name *component, const type data) {\
    pthread_rwlock_wrlock(&component->lock);\
    if (component->value) {\
        int new_length = component->length + 1;\
        int memory_length = (new_length) * sizeof(type);\
        type *new_memory = realloc(component->value, memory_length);\
        if (!new_memory) {\
            zox_log(" ! failed realloc memory in add_to_" #name "\n")\
            pthread_rwlock_unlock(&component->lock);\
            return 0;\
        }\
        component->value = new_memory;\
        component->length++;\
    } else {\
        initialize_memory_component(name, component, type, 1);\
    }\
    if (!component->value) {\
        component->length = 0;\
        pthread_rwlock_unlock(&component->lock);\
        return 0;\
    }\
    component->value[component->length - 1] = data;\
    pthread_rwlock_unlock(&component->lock);\
    return 1;\
}\
\
/* zeros pointer without a free */\
void zero_##name(name *ptr) {\
    if (ptr->length) {\
        if (is_log) {\
            zox_log("- zerod memory ["#name"] [%i]\n", ptr->length)\
        }\
        ptr->length = 0;\
    }\
    if (ptr->value) {\
        /*free(ptr->value);*/\
        ptr->value = NULL;\
    }\
}

#define zox_memory_component_removes(name, type)\
\
byte remove_at_##name(name *component, int index) {\
    if (!component->value || index < 0 || index >= component->length) {\
        return 0;\
    }\
    pthread_rwlock_wrlock(&component->lock);\
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
    pthread_rwlock_unlock(&component->lock);\
    return 1;\
}\
\
byte remove_from_##name(name *component, const type data) {\
    for (int i = 0; i < component->length; i++) {\
        if (component->value[i] == data) {\
            return remove_at_##name(component, i);\
        }\
    }\
    return 0;\
}


#define zox_define_memory_component2(name, ...)\
    zox_define_component(name)\
    ecs_set_hooks(world, name, {\
        .dtor = name##_dtor,\
        .move = name##_move,\
        .ctor = name##_ctor,\
        .copy = name##_copy,\
    });

#define clear_memory_component(name, component)\
    dispose_##name(component);

#define on_memory_component_created(component, name) {\
    if (component->value) {\
        total_memorys_allocated++;\
        name##_memorys_allocated++;\
    }\
}

#define resize_memory_component(name, component, type, new_length) {\
    if (component->length != new_length) {\
        if (new_length == 0) {\
            clear_memory_component(name, component)\
        } else if (component->value) {\
            type* new_memory = realloc(component->value, new_length * sizeof(type));\
            if (!new_memory) {\
                zox_log(" ! failure reallocing memory\n")\
            } else {\
                component->value = new_memory;\
                component->length = new_length;\
            }\
        } else {\
            initialize_memory_component(name, component, type, new_length);\
        }\
    }\
}
// this removes the character from chunk upon death


#define find_array_component_with_tag2(value, length, tag, name)\
    ecs_entity_t name = 0;\
    for (int i = 0; i < length; i++) {\
        if (zox_has(value[i], tag)) {\
            name = value[i];\
            break;\
        }\
    }

#define find_array_component_with_tag(component, tag, name)\
    ecs_entity_t name = 0;\
    for (int i = 0; i < component->length; i++) {\
        if (zox_has(component->value[i], tag)) {\
            name = component->value[i];\
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
