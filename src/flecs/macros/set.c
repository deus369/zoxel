#define zox_set_data(e, T, data)\
    ecs_set_id(world, e, ecs_id(T), sizeof(T), &data);

#define zox_set(e, T, ...) {\
    ecs_set_id(world, e, ecs_id(T), sizeof(T), &(T)__VA_ARGS__);\
}

#define zox_set_ptr(e, T, c)\
    ecs_set_ptr(world, e, T, &c);

#define zox_remove(e, T)\
    ecs_remove(world, e, T);


// ids

#define zox_id(name)\
    ecs_id(name)

#define zox_get_id(e, e2)\
    ecs_get_id(world, e, e2);

