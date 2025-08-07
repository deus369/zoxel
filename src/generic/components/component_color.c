component_id_list(color)

#define zox_component_color(name) zox_component(name, color)

#define zox_define_component_color(name)\
zox_define_component(name)\
add_to_entity_array_d(component_ids_color, ecs_id(name));

#define zox_component_string_color(component) " c[%i.%i.%i.%i]", component->value.r, component->value.g, component->value.b, component->value.a
