#define zox_instance(prefab)\
    const ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);

#define zox_instancee(prefab)\
    ecs_new_w_pair(world, EcsIsA, prefab);

#define zox_instance_named(prefab, name)\
    const ecs_entity_t name = ecs_new_w_pair(world, EcsIsA, prefab);

#define zox_prefab_child(prefab)\
    zox_instance(prefab)\
    zox_make_prefab(e)

#define zox_prefab_child_named(prefab, name)\
    zox_instance_named(prefab, name)\
    zox_make_prefab(name)

#define zox_clone(prefab)\
    const ecs_entity_t e = ecs_clone(world, 0, prefab, 1);

#define zox_instance_children(prefab)\
    zox_instance(prefab)\
    if (zox_has(prefab, Children)) {\
        zox_get_muter(e, Children, children)\
        zox_geter(prefab, Children, prefab_children)\
        for (int a = 0; a < children->length; a++) {\
            const ecs_entity_t e2 = zox_instancee(prefab_children->value[i]);\
            add_to_Children(children, e2)\
            zox_set(e2, ParentLink, { e })\
        }\
    }
