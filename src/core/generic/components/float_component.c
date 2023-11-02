component_id_list(float)

#define zox_component_float(name) zox_component(name, float)

#define zox_define_component_float(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_float, ecs_id(name));

