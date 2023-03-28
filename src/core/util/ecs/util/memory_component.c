// printf("Creating memory_component at [%p]\n", (void *)ptr);
//! ECS_CTOR The constructor should initialize the component value.
//! ECS_DTOR The destructor should free resources.
//! ECS_MOVE Copy a pointer from one component to another.
//! ECS_COPY Copy one data block to another.

//! Define a Memory component, with an array of a single data type.
#define zoxel_memory_component(name, type)\
typedef struct\
{\
    int length;\
    type *value;\
} name;\
ECS_COMPONENT_DECLARE(name);\
ECS_CTOR(name, ptr,\
{\
    ptr->length = 0;\
    ptr->value = NULL;\
})\
ECS_DTOR(name, ptr,\
{\
    if (ptr->value)\
    {\
        free(ptr->value);\
    }\
})\
ECS_MOVE(name, dst, src,\
{\
    if (dst->length != 0)\
    {\
        free(dst->value);\
    }\
    dst->value = src->value;\
    dst->length = src->length;\
    src->value = NULL;\
    src->length = 0;\
})\
ECS_COPY(name, dst, src, {\
    if (src->value)\
    {\
        if (dst->length != 0)\
        {\
            free(dst->value);\
        }\
        int memory_length = src->length * sizeof(type);\
        dst->length = src->length;\
        dst->value = malloc(memory_length);\
        if (dst->value != NULL) \
        {\
            dst->value = memcpy(dst->value, src->value, memory_length);\
        }\
    }\
})

#define zoxel_define_memory_component(name)\
    ECS_COMPONENT_DEFINE(world, name);\
    ecs_set_hooks(world, name, {\
        .ctor = ecs_ctor(name),\
        .move = ecs_move(name),\
        .copy = ecs_copy(name),\
        .dtor = ecs_dtor(name)\
    });

#define initialize_memory_component(component, dataType, length_)\
{\
    component->length = length_;\
    component->value = (dataType*) malloc(length_ * sizeof(dataType));\
}

#define initialize_memory_component_non_pointer(component, dataType, length_)\
    component.length = length_;\
    component.value = (dataType*) malloc(length_ * sizeof(dataType));

#define re_initialize_memory_component(component, dataType, length_)\
{\
    if (component->length != length_)\
    {\
        if (component->length != 0 && component->value)\
        {\
            free(component->value);\
        }\
        component->length = length_;\
        component->value = (dataType*) malloc(length_ * sizeof(dataType));\
    }\
}

#define re_initialize_memory_component_no_free(component, dataType, length_)\
{\
    if (component->length != length_)\
    {\
        component->length = length_;\
        component->value = (dataType*) malloc(length_ * sizeof(dataType));\
    }\
}

/*
        printf("Coping %i from %i.\n", dst->length, src->length);\
        for (int i = 0; i < dst->length; i++)\
        {\
            dst->value[i] = src->value[i];\
        }\
        if (dst->value != NULL) \
        {\
            dst->value = memcpy(dst->value, src->value, src->length);\
        }\
*/


// memset(component->value, 0, length_ * stride);
// printf("Freeing component %i.\n", component->length);
// printf("Freeing memory_component at [%p] - [%i]\n", (void *)component, component->length);
