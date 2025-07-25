#define zox_has_id(e, e2) \
    ecs_has_id(world, e, e2)

#define zox_set_id(e, id, size, data) \
    ecs_set_id(world, e, id, size, &(typeof(data)) { data });
