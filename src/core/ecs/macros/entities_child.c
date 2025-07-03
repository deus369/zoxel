#define zox_declare_component_entities_child(name, parent_name)\
\
zox_component_entity(name)\
\
void on_destroyed_##name(ecs_iter_t *it) {\
    zox_field_world()\
    zox_field_in(name, components, 1)\
    for (int i = 0; i < it->count; i++) {\
        zox_field_i(name, components, component)\
        const ecs_entity_t parent = component->value;\
        if (!zox_valid(parent) || !zox_has(parent, parent_name)) {\
            continue;\
        }\
        zox_field_e()\
        parent_name *parent_links = zox_get_mut(parent, parent_name)\
        if (remove_from_##parent_name(parent_links, e)) {\
            /*zox_log("! removed [%s] from [%s]\n", zox_get_name(e), zox_get_name(parent))*/\
            zox_modified(parent, parent_name)\
        }\
    }\
}

#define zox_define_component_entities_child(name)\
    zox_define_component_entity(name)\
    ecs_observer_init(world, &(ecs_observer_desc_t) {\
        .filter.expr = #name,\
        .callback = on_destroyed_##name,\
        .events = { EcsOnRemove },\
    });
