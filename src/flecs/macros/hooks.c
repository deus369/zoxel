#define zox_define_hooks(T) \
    ecs_set_hooks_id(world, ecs_id(T), &(ecs_type_hooks_t){ \
        .ctor = ecs_ctor(T), \
        .dtor = ecs_dtor(T), \
        .copy = ecs_copy(T), \
        .move = ecs_move(T), \
    })
