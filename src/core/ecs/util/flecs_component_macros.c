// used to define components inside a module declaration
#define zoxel_define_component(name)\
    ECS_COMPONENT_DEFINE(world, name);

#define zoxel_declare_tag(name)\
    ECS_DECLARE(name);

#define zoxel_define_tag(name)\
    ECS_TAG_DEFINE(world, name);

#define zoxel_component(name, type)\
typedef struct\
{\
    type value;\
} name;\
ECS_COMPONENT_DECLARE(name);

#define zoxel_byte_component(name)\
    zoxel_component(name, unsigned char);
    