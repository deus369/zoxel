#define zoxc_byte(name) \
    zoxc(name, byte)

#define zox_component_string_byte(c) \
    " b [%i]", c->value

zox_base_type(byte)

#define zoxd_byte(name)\
    zox_define_component(name)\
    add_to_entity_array_d(component_ids_byte, ecs_id(name));

