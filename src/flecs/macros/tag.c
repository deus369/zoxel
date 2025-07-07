#define zox_declare_tag(name)\
    ECS_DECLARE(name);

#define zox_define_tag(name)\
    ECS_TAG_DEFINE(world, name);

#define zox_add_tag_id(e, e2)\
    ecs_add_id(world, e, e2);

#define zox_add_tag(e, T)\
    ecs_add_id(world, e, ecs_id(T));

#define zox_remove_tag(e, T)\
    ecs_remove_id(world, e, ecs_id(T));
