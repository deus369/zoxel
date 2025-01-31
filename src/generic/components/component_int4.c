component_id_list(int4)

#define zox_component_int4(name) zox_component(name, int4)

#define zox_define_component_int4(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_int4, ecs_id(name));

#define zox_component_string_int4(component) " i4 [%ix%ix%ix%i]", component->value.x, component->value.y, component->value.z, component->value.w
