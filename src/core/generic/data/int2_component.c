component_id_list(int2)

#define zox_component_int2(name) zox_component(name, int2)

#define zox_define_component_int2(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_int2, ecs_id(name));
