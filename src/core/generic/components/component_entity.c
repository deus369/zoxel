component_id_list(ecs_entity_t)

#define zox_component_entity(name) zox_component(name, ecs_entity_t)

#define zox_define_component_entity(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_ecs_entity_t, ecs_id(name));

#define zox_component_string_ecs_entity_t(component) " e [%lu]", component->value
