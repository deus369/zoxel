component_id_list(int3)

#define zox_component_int3(name) zox_component(name, int3)

#define zox_define_component_int3(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_int3, ecs_id(name));

#define zox_component_string_int3(component) " i3 [%ix%ix%i]", component->value.x, component->value.y, component->value.z

zox_component_int3(Int3Stub)
