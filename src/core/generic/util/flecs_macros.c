//! My own flecs macros

#define zoxel_component(name, type)\
typedef struct\
{\
    type value;\
} name;\
ECS_COMPONENT_DECLARE(name)

// sizeof(type);    // 4 color
// sizeof(component->value); // 8, presumably pointer takes 4 more bytes?
// printf("Stride %i\n", stride);

#define initialize_memory_component(component, dataType, length_)\
{\
    component->length = length_;\
    component->value = (dataType*) malloc(length_ * sizeof(dataType));\
}

#define initialize_memory_component_non_pointer(component, dataType, length_)\
    component.length = length_;\
    component.value = (dataType*) malloc(length_ * sizeof(dataType));

// memset(component->value, 0, length_ * stride);
// printf("Freeing component %i.\n", component->length);
// printf("Freeing memory_component at [%p] - [%i]\n", (void *)component, component->length);

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

// printf("Creating memory_component at [%p]\n", (void *)ptr);
//! ECS_CTOR The constructor should initialize the component value.
//! ECS_DTOR The destructor should free resources.
//! ECS_MOVE Copy a pointer from one component to another.
//! ECS_COPY Copy one data block to another.

#define zoxel_memory_component_define(world, ComponentName)\
{\
    ECS_COMPONENT_DEFINE(world, ComponentName);\
    ecs_set_hooks(world, ComponentName, {\
        .ctor = ecs_ctor(ComponentName),\
        .move = ecs_move(ComponentName),\
        .copy = ecs_copy(ComponentName),\
        .dtor = ecs_dtor(ComponentName)\
    });\
}

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
    src->value = NULL;\
    dst->length = src->length;\
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

//! Creates a simple Filter with components.
#define zoxel_filter(name, world, ...)\
    ecs_query_t *name = ecs_query_init(world, &(ecs_query_desc_t) { \
        .filter.expr = #__VA_ARGS__});

// ecs_entity_t ecs_module_init(

#define zoxel_module(world, id, moduleName)\
ecs_entity_t ecs_id(id) = 0;\
{\
    ecs_component_desc_t desc = {0};\
    desc.entity = ecs_id(id);\
    ecs_id(id) = ecs_module_init(world, moduleName, &desc);\
    ecs_set_scope(world, ecs_id(id));\
}\
(void)ecs_id(id);

//! Adds a component but also adds override to an entity.
#define zoxel_add(world, entity, T)\
    ecs_add(world, entity, T);\
    ecs_override(world, entity, T)

// ecs_add_id(world, entity, ecs_id(T));
// ecs_override_id(world, entity, ecs_id(T))

//! Adds a component with data and also adds override to an entity.
#define zoxel_set(world, entity, T, ...)\
    ecs_set_id(world, entity, ecs_id(T), sizeof(T), &(T)__VA_ARGS__);\
    ecs_override_id(world, entity, ecs_id(T))

//! Adds a simple tag to an entity.
#define zoxel_add_tag(world, entity, T)\
    ecs_add_id(world, entity, ecs_id(T))



// Remember it will destroy the prefab ones too... *facepalm*



#define zoxel_reset_system(system_name, component_name)\
void system_name(ecs_iter_t *it)\
{\
    if (!ecs_query_changed(NULL, it))\
    {\
        return;\
    }\
    ecs_query_skip(it);\
    component_name *components = ecs_field(it, component_name, 1);\
    for (int i = 0; i < it->count; i++)\
    {\
        component_name *component = &components[i];\
        if (component->value == 1)\
        {\
            component->value = 0;\
        }\
    }\
}\
ECS_SYSTEM_DECLARE(system_name);

#define zoxel_reset_system_define(system_name, component_name)\
zoxel_system_main_thread(world, system_name, EcsPostUpdate, [out] component_name);
