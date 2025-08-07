component_id_list(float)

#define zox_component_float(name) zox_component(name, float)

#define zox_define_component_float(name)\
zox_define_component(name)\
add_to_entity_array_d(component_ids_float, ecs_id(name));

#define zox_component_string_float(component) " f [%.2f]", component->value
