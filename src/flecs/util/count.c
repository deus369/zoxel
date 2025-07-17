#define zox_count_ids(id)\
    ((int) ecs_count_id(world, id));

#define zox_count_types(type)\
    zox_count_ids(zox_id(type))
