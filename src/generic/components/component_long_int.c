component_id_list(long_int)

#define zox_component_long_int(name) zox_component(name, long int)

#define zox_define_component_long_int(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_long_int, ecs_id(name));

#define zox_component_string_long_int(component) " li [%ld]", component->value
