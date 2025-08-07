// zox_memory_component(ZoxName, byte)
component_id_list(zext)

#define zox_component_zext(name) zox_memory_component(name, byte)

#define zox_define_component_zext(name)\
zox_define_memory_component(name)\
add_to_entity_array_d(component_ids_zext, ecs_id(name));

#define zox_component_string_zext(component) " [%s]", convert_zext_to_text(component->value, component->length)
