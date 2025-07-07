#define zox_delete(e)\
    ecs_delete(world, e);

#define zox_delete_safe(e)\
    if (zox_valid(e)) {\
        zox_delete(e)\
    }

#define zox_delete_and_set(e)\
    if (e) {\
        zox_delete(e)\
        e = 0;\
    }
