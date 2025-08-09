component_id_list(long_int)

#define zoxc_long_int(name) \
    zoxc(name, long int)

#define zox_define_component_long_int(name)\
    zox_define_component(name)\
    add_to_entity_array_d(component_ids_long_int, ecs_id(name));

#define zox_component_string_long_int(component) \
    " li [%ld]", component->value
