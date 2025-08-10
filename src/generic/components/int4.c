#define zoxc_int4(name) \
     zoxc(name, int4)

#define zox_define_component_int4(name)\
    zox_define_component(name);\
    add_to_entity_array_d(component_ids_int4, ecs_id(name));

#define zox_component_string_int4(component) \
    " i4 [%ix%ix%ix%i]", component->value.x, component->value.y, component->value.z, component->value.w

zox_base_type(int4)
