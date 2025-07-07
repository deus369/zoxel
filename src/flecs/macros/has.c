#define zox_has(e, T)\
    ecs_has(world, e, T)

#define zox_has_id(e, e2)\
    ecs_has_id(world, e, e2)

#define zox_valid(e)\
    (e && ecs_is_valid(world, e) && ecs_is_alive(world, e))

#define zox_alive(e)\
    (e && ecs_is_alive(world, e))
