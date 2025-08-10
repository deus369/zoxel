#define zoxc_int(name) \
    zoxc(name, int)

#define zox_define_component_int(name)\
    zox_define_component(name)\
    add_to_entity_array_d(component_ids_int, ecs_id(name));

#define zox_component_string_int(component) \
    " i [%i]", component->value

zox_base_type(int)
