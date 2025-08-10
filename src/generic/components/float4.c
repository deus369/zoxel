#define zoxc_float4(name) \
    zoxc(name, float4)

#define zox_define_component_float4(name)\
    zox_define_component(name)\
    add_to_entity_array_d(component_ids_float4, ecs_id(name));

#define zox_component_string_float4(component) \
    " f4 [%.2fx%.2fx%.2fx%.2f]", component->value.x, component->value.y, component->value.z, component->value.w

zox_base_type(float4)
