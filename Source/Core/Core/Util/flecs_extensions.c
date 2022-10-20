//! My own flecs macros

#define ECS_COMPONENT_DEFINE_WITH_HOOKS(world, component)\
{\
    ECS_COMPONENT_DEFINE(world, component);\
    ecs_set_hooks(world, component, {\
        .ctor = ecs_ctor(component),\
        .move = ecs_move(component),\
        .copy = ecs_copy(component),\
        .dtor = ecs_dtor(component)\
    });\
}

#define ZOXEL_COMPONENT(componentName, valueType)\
typedef struct\
{\
    valueType value;\
} componentName;\
ECS_COMPONENT_DECLARE(componentName)

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