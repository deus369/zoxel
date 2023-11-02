component_id_list(byte)

#define zox_component_byte(name) zox_component(name, unsigned char)

#define zox_define_component_byte(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_byte, ecs_id(name));

#define zox_component_string_byte(component) " b [%i]", component->value

// zox_log("   + byte_component [%lu]\n", ecs_id(name))
