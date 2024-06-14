component_id_list(entity)

#define zox_component_entity(name) zox_component(name, ecs_entity_t)

#define zox_define_component_entity(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_entity, ecs_id(name));

#define zox_component_string_entity(component) " e [%llu]", component->value

// add to tilemap link
#define zox_component_parented(name) zox_component_entity(name)\
void on_destroyed##_##name(ecs_iter_t *it) {\
    zox_iter_world()\
    zox_field_out(name, components, 1)\
    for (int i = 0; i < it->count; i++) {\
        zox_field_o(name, components, component)\
        zox_delete(component->value);\
        component->value = 0;\
    }\
}
