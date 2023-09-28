int memorys_allocated = 0;

// an array of a single data type
// uses:
//      ECS_CTOR The constructor should initialize the component value
//      ECS_DTOR The destructor should free resources
//      ECS_MOVE Copy a pointer from one component to another
//      ECS_COPY Copy one data block to another
#define zox_memory_component(name, type)\
typedef struct {\
    int length;\
    type *value;\
} name; zox_custom_component(name)\
void zero##_##name(name *ptr) {\
    ptr->value = NULL;\
    ptr->length = 0;\
}\
void dispose##_##name(name *ptr) {\
    if (!ptr->value) return;\
    free(ptr->value);\
    zero##_##name(ptr);\
    memorys_allocated--;\
    /*zox_logg("      memorys decreased (disposed)\n")*/\
}\
ECS_CTOR(name, ptr, { zero##_##name(ptr); })\
ECS_DTOR(name, ptr, { dispose##_##name(ptr); })\
ECS_MOVE(name, dst, src, {\
    if (dst->value == src->value) return;\
    /* clear dst first */\
    dispose##_##name(dst);\
    /* copy src contents to dst */\
    dst->length = src->length;\
    dst->value = src->value;\
    /* lastly clear src */\
    zero##_##name(src);\
})\
ECS_COPY(name, dst, src, {\
    if (!src->value) {\
        dispose##_##name(dst);\
    } else {\
        int memory_length = src->length * sizeof(type);\
        if (dst->value) dispose##_##name(dst);\
        dst->length = src->length;\
        dst->value = memcpy(malloc(memory_length), src->value, memory_length);\
        memorys_allocated++;\
    }\
})\

#define zox_define_memory_component2(name, ...)\
zox_define_component(name)\
ecs_set_hooks(world, name, {\
    .ctor = ecs_ctor(name),\
    .move = ecs_move(name),\
    .copy = ecs_copy(name),\
    .dtor = ecs_dtor(name)\
});

#define zox_define_memory_component(name) zox_define_memory_component2(name, [out] name)

#define clear_memory_component(component) {\
    if (component->value) {\
        free(component->value);\
        component->value = NULL;\
        component->length = 0;\
        memorys_allocated--;\
        /*zox_logg("      memorys decreased (clear_memory)\n")*/\
    }\
}

#define initialize_memory_component(component, data_type, new_length) {\
    if (component->length != new_length) {\
        if (new_length == 0) {\
            clear_memory_component(component);\
        } else {\
            component->length = new_length;\
            component->value = malloc(component->length * sizeof(data_type));\
            memorys_allocated++;\
        }\
    }\
}

#define re_initialize_memory_component(component, data_type, new_length) {\
    if (component->length != new_length) {\
        if (new_length == 0) {\
            clear_memory_component(component);\
        } else if (component->value) {\
            component->length = new_length;\
            component->value = realloc(component->value, component->length * sizeof(data_type));\
        } else {\
            initialize_memory_component(component, data_type, new_length);\
        }\
    }\
}

#define add_to_memory_component(component, data_type, data) {\
    if (component->value != NULL) {\
        unsigned char has_data = 0;\
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
    }\
}

#define remove_from_memory_component(component, data_type, data) {\
    if (component->value != NULL) {\
        int index = -1;\
        for (int i = 0; i < component->length; i++) {\
            if (component->value[i] == data) {\
                index = i;\
                break;\
            }\
        }\
        if (index != -1) {\
            for (int i = index; i < component->length - 1; i++) {\
                component->value[i] = component->value[i + 1];\
            }\
            component->length--;\
            component->value = realloc(component->value, component->length * sizeof(data_type));\
        }\
    }\
}

// if (ptr->value) { zox_logg("      memorys decreased (dtor)\n") } 

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
