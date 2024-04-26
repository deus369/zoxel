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

void ecs_override_remove_id(ecs_world_t *world, ecs_entity_t entity, ecs_id_t id) {
    ecs_remove_id(world, entity, ECS_OVERRIDE | id);
    // ecs_add_id(world, entity, ECS_OVERRIDE | id);
}

#define zox_override_remove(e, T) ecs_override_remove_id(world, e, ecs_id(T));

#define zox_override(e, T) ecs_override_id(world, e, ecs_id(T));

#define zox_prefab_set(e, T, ...) {\
    ecs_set_id(world, e, ecs_id(T), sizeof(T), &(T)__VA_ARGS__);\
    zox_override(e, T)\
}

#define zox_delete(e) ecs_delete(world, e);

#define zox_delete_and_set(e)\
if (e) {\
    zox_delete(e)\
    e = 0;\
}

#define zox_add_tag(e, T) ecs_add_id(world, e, ecs_id(T));

#define zox_remove_tag(e, T) ecs_remove_id(world, e, ecs_id(T));

#define zox_make_prefab(e) ecs_add_id(world, e, EcsPrefab);

#define zox_has(e, T) ecs_has(world, e, T)

#define zox_gett_value(e, T) ecs_get(world, e, T)->value

#define zox_gett(e, T) ecs_get(world, e, T)

#define zox_get(e, T) ecs_get(world, e, T);

#define zox_get_value(e, T) ecs_get(world, e, T)->value;

#define zox_get_mut(e, T) ecs_get_mut(world, e, T);

#define zox_modified(e, T) ecs_modified(world, e, T);

#define zox_set_mut(e, type, valuer) {\
    type *component = zox_get_mut(e, type)\
    if (component->value != valuer) {\
        component->value = valuer;\
        zox_modified(e, type)\
    }\
}

// ecs_entity_t e = ecs_new_prefab(world, "");
#define zox_prefab()\
    const ecs_entity_t e = ecs_new(world, 0);\
    zox_make_prefab(e)

// ecs_add_id(world, e, EcsPrefab);
// zox_add_tag(e, EcsPrefab)

#define zox_instance(prefab) const ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);

#define zox_prefab_child(prefab)\
    zox_instance(prefab)\
    zox_make_prefab(e)

#define zox_clone(prefab) const ecs_entity_t e = ecs_clone(world, 0, prefab, 1);

// checks if entity is valid
#define zox_valid(e) ecs_is_valid(world, e)
#define zox_alive(e) ecs_is_alive(world, e)
