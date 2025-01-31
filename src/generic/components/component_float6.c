component_id_list(float6)

#define zox_component_float6(name) zox_component(name, float6)

#define zox_define_component_float6(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_float6, ecs_id(name));

#define zox_component_string_float6(component) " f6 [%.2fx%.2fx%.2fx%.2fx%.2fx%.2f]", component->value.x, component->value.y, component->value.z, component->value.w, component->value.u, component->value.v
