#define zox_add(e, T) {\
    ecs_add(world, e, T);\
    ecs_override(world, e, T);\
}

#define zox_add_only(e, T) ecs_add(world, e, T);

#define zox_remove(e, T) ecs_remove(world, e, T);

#define zox_prefab_add(e, T)\
ecs_add(world, e, T);\
ecs_override_id(world, e, ecs_id(T));

#define zox_set_data(e, T, data) ecs_set_id(world, e, ecs_id(T), sizeof(T), &data);

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

#define zox_delete_safe(e) if (zox_valid(e)) zox_delete(e)

#define zox_delete_and_set(e)\
if (e) {\
    zox_delete(e)\
    e = 0;\
}

// returns entity for a name
#define zox_id(name) ecs_id(name)

#define zox_add_tag_id(e, e2) ecs_add_id(world, e, e2);

#define zox_add_tag(e, T) ecs_add_id(world, e, ecs_id(T));

#define zox_remove_tag(e, T) ecs_remove_id(world, e, ecs_id(T));

#define zox_make_prefab(e) ecs_add_id(world, e, EcsPrefab);

#define zox_has(e, T) ecs_has(world, e, T)

#define zox_has_id(e, e2) ecs_has_id(world, e, e2)

#define zox_gett_value(e, T) ecs_get(world, e, T)->value

#define zox_get_value_(e, T) ecs_get(world, e, T)->value

#define zox_get_length_(e, T) ecs_get(world, e, T)->length

#define zox_gett(e, T) ecs_get(world, e, T)

#define zox_get(e, T) ecs_get(world, e, T);

#define zox_geter(e, T, name) const T *name = zox_get(e, T)

#define zox_get_value(e, T) ecs_get(world, e, T)->value;

#define zox_get_mut(e, T) ecs_get_mut(world, e, T);

#define zox_get_mutt(e, type, name) type *name = zox_get_mut(e, type)

#define zox_modified(e, type) ecs_modified(world, e, type);

#define zox_get_muter(e, type, name)\
zox_get_mutt(e, type, name)\
zox_modified(e, type)

#define zox_set_mut(e, type, valuer) {\
    type *component = zox_get_mut(e, type)\
    if (component->value != valuer) {\
        component->value = valuer;\
        zox_modified(e, type)\
    }\
}

#define zox_new() const ecs_entity_t e = ecs_new(world, 0);

#define zox_neww(name) const ecs_entity_t name = ecs_new(world, 0);

// ecs_entity_t e = ecs_new_prefab(world, "");
#define zox_prefab()\
zox_new()\
zox_make_prefab(e)

// ecs_add_id(world, e, EcsPrefab);
// zox_add_tag(e, EcsPrefab)

#define zox_instance(prefab)\
const ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);

#define zox_instance_children(prefab)\
zox_instance(prefab)\
if (zox_has(prefab, Children)) {\
    zox_get_muter(e, Children, children)\
    const Children *prefab_children = zox_get(prefab, Children)\
    for (int a = 0; a < children->length; a++) {\
        const ecs_entity_t e2 = zox_instancee(prefab_children->value[i]);\
        add_to_Children(children, e2)\
        zox_set(e2, ParentLink, { e })\
    }\
}

#define zox_instancee(prefab) ecs_new_w_pair(world, EcsIsA, prefab);

#define zox_prefab_child(prefab)\
    zox_instance(prefab)\
    zox_make_prefab(e)

#define zox_clone(prefab) const ecs_entity_t e = ecs_clone(world, 0, prefab, 1);

// checks if entity is valid
#define zox_valid(e) (e && ecs_is_valid(world, e))
#define zox_alive(e) (e && ecs_is_alive(world, e))

// using IDs (entities for types)


#define zox_get_id(e, e2) ecs_get_id(world, e, e2);


// Retrieve the prefab (parent) from the entity
#define zox_get_prefab(e, name) const ecs_entity_t name = ecs_get_target(world, e, EcsIsA, 0);
