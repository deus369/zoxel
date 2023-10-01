#define zox_filter(name, ...) ecs_query_t *name = ecs_query_init(world, &(ecs_query_desc_t) { .filter.expr = #__VA_ARGS__});

#define zox_add(e, T) {\
    ecs_add(world, e, T);\
    ecs_override(world, e, T);\
}

#define zox_add_only(e, T) ecs_add(world, e, T);

#define zox_remove(e, T) ecs_remove(world, e, T);

#define zox_add_new(e, T, ...) {\
    ecs_set_id(world, e, ecs_id(T), sizeof(T), &(T)__VA_ARGS__);\
    ecs_override_id(world, e, ecs_id(T));\
}

#define zox_set(e, T, ...) {\
    ecs_set_id(world, e, ecs_id(T), sizeof(T), &(T)__VA_ARGS__);\
}

#define zox_prefab_set(e, T, ...) {\
    ecs_set_id(world, e, ecs_id(T), sizeof(T), &(T)__VA_ARGS__);\
    ecs_override_id(world, e, ecs_id(T));\
}

#define zox_delete(e) ecs_delete(world, e);

#define zox_add_tag(e, T) ecs_add_id(world, e, ecs_id(T));

#define zox_make_prefab(e) ecs_add_id(world, e, EcsPrefab);

#define zox_has(e, T) ecs_has(world, e, T)

#define zox_get(e, T) ecs_get(world, e, T);

#define zox_get_mut(e, T) ecs_get_mut(world, e, T);

#define zox_modified(e, T) ecs_modified(world, e, T);

#define zox_prefab() ecs_entity_t e = ecs_new_prefab(world, "");

#define zox_instance(prefab) ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);

#define zox_prefab_child(prefab) zox_instance(prefab)\
    zox_make_prefab(e)

#define zox_clone(prefab) ecs_entity_t e = ecs_clone(world, 0, prefab, 1);