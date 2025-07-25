// #define zox_debug_spawning

#define zox_get_name(e)\
    ecs_get_name(world, e)

#define zox_set_name(e, name)\
    ecs_set_name(world, e, name);

#define zox_get_name_type(type)\
    zox_get_name(ecs_id(type))

#define zox_get_namespace(e)\
    ecs_get_fullpath(world, e)

#define zox_sys_e_name\
    ecs_get_name(it->world, it->entities[i])
