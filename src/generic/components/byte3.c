#define zoxc_byte3(name)\
    zoxc(name, byte3)

#define zoxd_byte3(name)\
    zox_define_component(name)\
    add_to_entity_array_d(component_ids_byte3, ecs_id(name));

#define zox_component_string_byte3(component)\
    " b3 [%ix%ix%i]", component->value.x, component->value.y, component->value.z

zox_base_type(byte3)
