#ifdef zox_flecs_4

    #define zox_get_new()\
        ecs_new(world);

#else

    #define zox_get_new()\
        ecs_new(world, 0);

#endif

#define zox_new()\
    const ecs_entity_t e = zox_get_new();

#define zox_neww(name)\
    const ecs_entity_t name = zox_get_new();

#define zox_instance(prefab)\
    const ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);

#define zox_instancee(prefab)\
    ecs_new_w_pair(world, EcsIsA, prefab);

#define zox_instance_named(prefab, name)\
    const ecs_entity_t name = ecs_new_w_pair(world, EcsIsA, prefab);
