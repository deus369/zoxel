#ifdef zox_flecs_4

    #define zox_override_tag ECS_AUTO_OVERRIDE

    #define zox_is_override(id)\
        ECS_HAS_ID_FLAG(id, AUTO_OVERRIDE)

    #define zox_override(e, T)\
        ecs_auto_override_id(world, e, zox_id(T));

    // make the instance inherit the prefabs component value
    #define zox_inherit(e, T)\
        ecs_add_pair(world, ecs_id(T), EcsOnInstantiate, EcsInherit);

#else

    #define zox_override_tag ECS_OVERRIDE

    #define zox_is_override(id)\
        ECS_HAS_ID_FLAG(id, OVERRIDE)

    #define zox_override(e, T)\
        ecs_override_id(world, e, zox_id(T));

#endif

#define zox_remove_override(e, T)\
    ecs_override_remove_id(world, e, zox_override_tag | zox_id(T));
