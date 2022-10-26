//! My own flecs macros

#define ZOXEL_COMPONENT(name, type)\
typedef struct\
{\
    type value;\
} name;\
ECS_COMPONENT_DECLARE(name)


//! ECS_CTOR The constructor should initialize the component value.
//! ECS_DTOR The destructor should free resources.
//! ECS_MOVE Copy a pointer from one component to another.
//! ECS_COPY Copy one data block to another.

#define ZOXEL_DEFINE_MEMORY_COMPONENT(world, ComponentName)\
{\
    ECS_COMPONENT_DEFINE(world, ComponentName);\
    ecs_set_hooks(world, ComponentName, {\
        .ctor = ecs_ctor(ComponentName),\
        .move = ecs_move(ComponentName),\
        .copy = ecs_copy(ComponentName),\
        .dtor = ecs_dtor(ComponentName)\
    });\
}

// sizeof(type);    // 4 color
// sizeof(component->value); // 8, presumably pointer takes 4 more bytes?
// printf("Stride %i\n", stride);

#define initialize_memory_component(component, dataType, length_)\
{\
    int length = length_;\
    const int stride = sizeof(dataType);\
    component->length = length;\
    component->value = malloc(length * stride);\
}

//! Define a Memory component, with an array of a single data type.
#define ZOXEL_DECLARE_MEMORY_COMPONENT(name, type)\
typedef struct\
{\
    int length;\
    type *value;\
} name;\
ECS_COMPONENT_DECLARE(name);\
ECS_CTOR(name, ptr,\
{\
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
    free(dst->value);\
    dst->value = src->value;\
    src->value = NULL;\
})\
ECS_COPY(name, dst, src, {\
    if (src->value)\
    {\
        int memoryLength = src->length;\
        free(dst->value);\
        dst->value = malloc(memoryLength);\
        if (dst->value != NULL) \
        {\
            dst->value = memcpy(dst->value, src->value, memoryLength);\
        }\
    }\
})

//! Multithreaded System Definitions.
#define ZOXEL_SYSTEM_MULTITHREADED(world, id_, phase, ...)\
    { \
        ecs_system_desc_t desc = {0}; \
        ecs_entity_desc_t edesc = {0}; \
        edesc.id = ecs_id(id_);\
        edesc.name = #id_;\
        edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0); \
        edesc.add[1] = (phase); \
        desc.entity = ecs_entity_init(world, &edesc);\
        desc.query.filter.expr = #__VA_ARGS__; \
        desc.callback = id_; \
        desc.multi_threaded = 1; \
        ecs_id(id_) = ecs_system_init(world, &desc); \
    } \
    ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);


// ECS Helper functions
// void ecs_system_enable_multithreading(ecs_world_t *world, long int function)
// {
//     ecs_system_init(world, &(ecs_system_desc_t) { .entity = function, .multi_threaded = 1 } );
// }

// can debug destruction
// printf("Destroying name Memory.\n");