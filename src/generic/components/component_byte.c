component_id_list(byte)

#define zox_component_byte(name) zox_component(name, byte)

#define zox_define_component_byte(name)\
zox_define_component(name)\
add_to_entity_array_d(component_ids_byte, ecs_id(name));

#define zox_component_string_byte(component) " b [%i]", component->value
