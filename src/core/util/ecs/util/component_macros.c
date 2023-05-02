// used to define components inside a module declaration
#define zoxel_define_component(name)\
    ECS_COMPONENT_DEFINE(world, name);

#define zoxel_declare_tag(name)\
    ECS_DECLARE(name);

#define zoxel_define_tag(name)\
    ECS_TAG_DEFINE(world, name);

#define zoxel_component(name, type)\
typedef struct {\
    type value;\
} name;\
ECS_COMPONENT_DECLARE(name);

#define zoxel_byte_component(name) zoxel_component(name, unsigned char)

#define zoxel_time_component(name) zoxel_component(name, double)

#define zoxel_hashmap_component(name, type)\
    zoxel_component(name, type##_##hash_map*)\
    ECS_DTOR(name, ptr, {\
        if (ptr->value != NULL) {\
            type##_##hash_map_dispose(ptr->value);\
        }\
    })

#define zoxel_define_hashmap_component(name)\
    zoxel_define_component(name)\
    ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });



#define zoxel_custom_component(name) ECS_COMPONENT_DECLARE(name);