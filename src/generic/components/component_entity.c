component_id_list(entity)

#define zox_component_entity(name)\
    zox_component(name, ecs_entity_t)

#define zox_define_component_entity(name)\
    zox_define_component(name)\
    add_to_ecs_entity_t_array_d(component_ids_entity, ecs_id(name));

#define zox_component_string_entity(component) " e [%lu]", component->value

// add to tilemap link
#define zox_component_parented(name) zox_component_entity(name)\
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
