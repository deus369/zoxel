#define zox_define_component(name) ECS_COMPONENT_DEFINE(world, name);

#define zox_define_component_w_dest(name) zox_define_component(name)\
    ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });

#define zox_define_destruction(name) ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });

#define zox_declare_tag(name) ECS_DECLARE(name);

#define zox_define_tag(name) ECS_TAG_DEFINE(world, name);

#define zox_component(name, type)\
typedef struct {\
    type value;\
} name;\
ECS_COMPONENT_DECLARE(name);

#define zox_function_component(name, return_type, ...)\
typedef struct {\
    return_type (*value)(__VA_ARGS__);\
} name;\
ECS_COMPONENT_DECLARE(name);

#define zox_byte_component(name) zox_component(name, unsigned char)

#define zox_time_component(name) zox_component(name, double)

#define zox_entity_component(name) zox_component(name, ecs_entity_t)

#define zox_hashmap_component(name, type)\
zox_component(name, type##_##hash_map*)\
ECS_DTOR(name, ptr, {\
    if (ptr->value != NULL) type##_##hash_map_dispose(ptr->value);\
})

#define zox_define_hashmap_component(name)\
    zox_define_component(name)\
    ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });

#define zox_custom_component(name) ECS_COMPONENT_DECLARE(name);