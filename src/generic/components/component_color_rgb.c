component_id_list(color_rgb)

#define zox_component_color_rgb(name) zox_component(name, color_rgb)

#define zox_define_component_color_rgb(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_color_rgb, ecs_id(name));

#define zox_component_string_color_rgb(component) " c[%i.%i.%i]", component->value.r, component->value.g, component->value.b
