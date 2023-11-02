component_id_list(int)

#define zox_component_int(name) zox_component(name, int)

#define zox_define_component_int(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_int, ecs_id(name));
