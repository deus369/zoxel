component_id_list(byte2)

#define zox_component_byte2(name) zox_component(name, byte2)

#define zox_define_component_byte2(name)\
zox_define_component(name)\
add_to_entity_array_d(component_ids_byte2, ecs_id(name));

#define zox_component_string_byte2(component) " b2 [%ix%i]", component->value.x, component->value.y
