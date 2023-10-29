/*ecs_entity_t_array_d* int2_component_ids;

void initialize_component_ids_int2() {
    int2_component_ids = create_ecs_entity_t_array_d();
}

void dispose_component_ids_int2() {
    dispose_ecs_entity_t_array_d(int2_component_ids);
}

#define zox_is_component_int2(id) is_in_ecs_entity_t_array_d(int2_component_ids, id)

#define zox_component_int2(name) zox_component(name, int2)

#define zox_define_component_int2(name)\
ECS_COMPONENT_DEFINE(world, name);\
add_to_ecs_entity_t_array_d(int2_component_ids, ecs_id(name));*/

// zox_log("   + byte_component [%lu]\n", ecs_id(name))


component_id_list(int2)

#define zox_component_int2(name) zox_component(name, int2)

#define zox_define_component_int2(name)\
zox_define_component(name)\
add_to_ecs_entity_t_array_d(component_ids_int2, ecs_id(name));
