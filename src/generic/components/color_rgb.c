#define zoxc_color_rgb(name) \
    zoxc(name, color_rgb)

#define zox_define_component_color_rgb(name)\
    zox_define_component(name)\
    add_to_entity_array_d(component_ids_color_rgb, ecs_id(name));

#define zox_component_string_color_rgb(component)\
    " c[%i.%i.%i]", component->value.r, component->value.g, component->value.b

zox_base_type(color_rgb)
