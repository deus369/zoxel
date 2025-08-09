#define zoxc_child(name, parent_name)\
zoxc_entity(name);\
\
void on_destroyed_##name(ecs_iter_t *it) {\
    zox_sys_world()\
    zox_sys_begin()\
    zox_sys_in(name)\
    for (int i = 0; i < it->count; i++) {\
        zox_sys_i(name, component)\
        const ecs_entity_t parent = component->value;\
        if (!zox_valid(parent) || !zox_has(parent, parent_name)) {\
            continue;\
        }\
        zox_sys_e()\
        parent_name *parent_links = zox_get_mut(parent, parent_name)\
        if (remove_from_##parent_name(parent_links, e)) {\
            /*zox_log("! removed [%s] from [%s]\n", zox_get_name(e), zox_get_name(parent))*/\
            zox_modified(parent, parent_name)\
        }\
    }\
}

#define zox_define_component_entities_child(name)\
    zox_define_component_entity(name)\
    zox_observe_expr(on_destroyed_##name, EcsOnRemove, "[in] "#name)
