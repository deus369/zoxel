component_id_list(float3)

#define zox_component_float3(name) zox_component(name, float3)

#define zox_define_component_float3(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_float3, ecs_id(name));

#define zox_component_string_float3(component) " f3 [%.2fx%.2fx%.2f]", component->value.x, component->value.y, component->value.z
