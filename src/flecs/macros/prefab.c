#define zox_make_prefab(e)\
    ecs_add_id(world, e, EcsPrefab);

#define zox_prefab()\
    zox_new()\
    zox_make_prefab(e)

#ifdef zox_flecs_4

    // flecs 4 overrides by default
    #define zox_prefab_add(e, T)\
        ecs_add(world, e, T);

#else

    // flecs 3 inherits parent data by default
    #define zox_prefab_add(e, T)\
        ecs_add(world, e, T);\
        zox_override(e, T)

#endif

#define zox_prefab_set(e, T, ...) {\
    zox_prefab_add(e, T) \
    ecs_set_id(world, e, ecs_id(T), sizeof(T), &(T)__VA_ARGS__); \
}

// Retrieve the prefab (parent) from the entity
#define zox_get_prefab(e, name)\
    const ecs_entity_t name = ecs_get_target(world, e, EcsIsA, 0);
