int total_memorys_allocated = 0;

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

#define zox_memory_component(name, type) zox_memory_component_debug(name, type, 0)

#define zox_memory_component_debug(name, type, is_log)\
int name##_memorys_allocated = 0;\
typedef struct {\
    int length;\
    type *value;\
} name;\
zox_custom_component(name)\
\
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
}\
\
void dispose_##name(name *ptr) {\
    if (!ptr->value && !ptr->length) {\
        return;\
    }\
    free(ptr->value);\
    zero_##name(ptr);\
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
byte add_to_##name(name *component, const type data) {\
    if (component->value) {\
        int new_length = component->length + 1;\
        int memory_length = (new_length) * sizeof(type);\
        type *new_memory = realloc(component->value, memory_length);\
        if (!new_memory) {\
            zox_log(" ! failed realloc memory in add_to_" #name "\n")\
            return 0;\
        }\
        component->value = new_memory;\
        component->length++;\
    } else {\
        initialize_memory_component(name, component, type, 1);\
    }\
    if (!component->value) {\
        component->length = 0;\
        return 0;\
    }\
    component->value[component->length - 1] = data;\
    return 1;\
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
    name *arr = ptr;\
    for (int i = 0; i < count; i++) {\
        arr[i].length = 0;\
        arr[i].value = NULL;\
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
}

#define zox_define_memory_component2(name, ...)\
    zox_define_component(name)\
    ecs_set_hooks(world, name, {\
        .dtor = name##_dtor,\
        .move = name##_move,\
        .ctor = name##_ctor,\
        .copy = name##_copy,\
    });


#define zox_define_memory_component(name) zox_define_memory_component2(name, [out] name)

#define clear_memory_component(name, component) dispose_##name(component);

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

#define remove_from_memory_component(component, type, data) {\
    if (component->value) {\
        int index = -1;\
        for (int i = 0; i < component->length; i++) {\
            if (component->value[i] == data) {\
                index = i;\
                break;\
            }\
        }\
        if (index != -1) {\
            for (int i = index; i < component->length - 1; i++) component->value[i] = component->value[i + 1];\
            component->length--;\
            if (!component->length) {\
                free(component->value);\
                component->value = NULL;\
            } else {\
                component->value = realloc(component->value, component->length * sizeof(type));\
            }\
        }\
    }\
}
// this removes the character from chunk upon death

#define zox_link_component(name, type, links_name, ...)\
zox_component(name, type)\
void on_destroyed##_##name(ecs_iter_t *it) {\
    zox_field_world()\
    name *components = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        zox_field_e()\
        name *component = &components[i];\
        if (component->value && zox_valid(component->value)) {\
            links_name *links_component = zox_get_mut(component->value, links_name)\
            remove_from_memory_component(links_component, type, e)\
            zox_modified(component->value, links_name)\
        }\
        component->value = 0;\
    }\
}

#define zox_define_links_component2(name, ...)\
zox_define_component(name)\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed_##name,\
    .events = { EcsOnRemove },\
});

#define zox_define_links_component(name) zox_define_links_component2(name, [out] name)

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

/*
.ctor = ecs_ctor(name),\
.dtor = ecs_dtor(name),\
.move = ecs_move(name),\
.copy = ecs_copy(name),
*/

/*

ECS_CTOR(name, ptr, {\
    ptr->length = 0;\
    ptr->value = NULL;\
})

 ECS_DTOR(name, ptr, {\
 if (!ptr->length) return;\
     if (is_log) {\
         zox_log("[memory] dtor ["#name"] [%i]\n", ptr->length)\
         }\
         free(ptr->value);\
         ptr->length = 0;\
         ptr->value = NULL;\
         })\

ECS_MOVE(name, dst, src, {\
    if (dst->value == src->value) return;\
    if (!dst->length && !src->length) return;\
    if (is_log) {\
        zox_log("[memory] moving ["#name"] [%i to %i]\n", src->length, dst->length)\
    }\
    dst->length = src->length;\
    dst->value = src->value;\
    src->value = NULL;\
    src->length = 0;\
})

\
ECS_CTOR(name, ptr, {\
    name *comp = ptr;\
    comp->length = 0;\
    comp->value = NULL;\
})\

\
ECS_COPY(name, dst, src, {\
    if (!dst->length && !src->length) return;\
    if (is_log) {\
        zox_log("[memory] copying ["#name"] [%i to %i]\n", src->length, dst->length)\
    }\
    clone_##name(dst, src);\
})\

*/

/*
#define add_to_memory_component(component, data_type, data) {\
    if (component->value) {\
        byte has_data = 0;\
        for (int i = 0; i < component->length; i++) {\
            if (component->value[i] == data) {\
                has_data = 1;\
                break;\
            }\
        }\
        if (!has_data) {\
            component->length++;\
            component->value = realloc(component->value, component->length * sizeof(data_type));\
            component->value[component->length - 1] = data;\
        }\
    } else {\
        component->length = 1;\
        component->value = malloc(sizeof(data_type));\
        component->value[0] = data;\
    }\
}
*/

// if (ptr->value) { zox_log("      memorys decreased (dtor)\n") }

/*void on_destroyed##_##name(ecs_iter_t *it) {\
    name *components = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        name *component = &components[i];\
        dispose##_##name(component);\
    }\
}*/

/*ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});*/


// an array of a single data type
// uses:
//      ECS_CTOR The constructor should initialize the component value
//      ECS_DTOR The destructor should free resources
//      ECS_MOVE Copy a pointer from one component to another
//      ECS_COPY Copy one data block to another

