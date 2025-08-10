#define zoxc_byte2(name) \
    zoxc(name, byte2)

#define zoxd_byte2(name)\
    zox_define_component(name)\
    add_to_entity_array_d(component_ids_byte2, ecs_id(name));

#define zox_component_string_byte2(c) \
    " b2 [%ix%i]", c->value.x, c->value.y

zox_base_type(byte2)