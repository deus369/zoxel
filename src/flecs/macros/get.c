#define zox_gett_value(e, T)\
    ecs_get(world, e, T)->value

#define zox_get_value_(e, T)\
    ecs_get(world, e, T)->value

#define zox_get_length_(e, T)\
    ecs_get(world, e, T)->length

#define zox_gett(e, T)\
    ecs_get(world, e, T)

#define zox_get(e, T)\
    ecs_get(world, e, T);

#define zox_geter(e, T, name)\
    const T *name = zox_get(e, T)

#define zox_get_value(e, type)\
    ecs_get(world, e, type)->value;

#define zox_geter_value(e, component_type, type, name)\
    const type name = zox_get_value(e, component_type)

#define zox_geter_value2(e, component_type, type, name)\
    type name = zox_get_value(e, component_type)

#define zox_geter_value_safe(e, component_type, type, name)\
    const type name = zox_has(e, component_type) ? zox_gett_value(e, component_type) : 0;

#define zox_get_path(e)\
    ecs_get_path_w_sep(world, 0, e, ".", NULL)
