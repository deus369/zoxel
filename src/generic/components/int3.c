#define zoxc_int3(name) \
    zoxc(name, int3)

#define zox_define_component_int3(name)\
    zox_define_component(name)\
    add_to_entity_array_d(component_ids_int3, ecs_id(name));

#define zox_component_string_int3(component) \
    " i3 [%ix%ix%i]", component->value.x, component->value.y, component->value.z

zox_base_type(int3)
