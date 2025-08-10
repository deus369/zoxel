#define zoxc_entity(name)\
    zoxc(name, entity)

#define zox_define_component_entity(name)\
    zox_define_component(name)\
    add_to_entity_array_d(component_ids_entity, ecs_id(name));

#define zox_component_string_entity(c) \
    " e [%s]", zox_valid(c->value) ? zox_get_name(c->value) : "0"

    // " e [%lu]", component->value


zox_base_type(entity)

// add to tilemap link
#define zox_component_parented(name) zoxc_entity(name)\
    void on_destroyed##_##name(ecs_iter_t *it) {\
        zox_sys_world()\
        zox_sys_begin()\
        zox_sys_out(name)\
        for (int i = 0; i < it->count; i++) {\
            zox_sys_o(name, component)\
            zox_delete(component->value);\
            component->value = 0;\
        }\
    }