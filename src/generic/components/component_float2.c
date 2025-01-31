component_id_list(float2)

#define zox_component_float2(name) zox_component(name, float2)

#define zox_define_component_float2(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_float2, ecs_id(name));

#define zox_component_string_float2(component) " f2 [%.2fx%.2f]", component->value.x, component->value.y
