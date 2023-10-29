/*ecs_entity_t_array_d* byte_component_ids;

void initialize_component_ids_byte() {
    byte_component_ids = create_ecs_entity_t_array_d();
}

void dispose_component_ids_byte() {
    dispose_ecs_entity_t_array_d(byte_component_ids);
}
#define zox_is_component_byte(id) is_in_ecs_entity_t_array_d(component_ids_byte, id)

*/

component_id_list(byte)

#define zox_byte_component(name) zox_component(name, unsigned char)

#define zox_define_component_byte(name)\
ECS_COMPONENT_DEFINE(world, name);\
add_to_ecs_entity_t_array_d(component_ids_byte, ecs_id(name));

// zox_log("   + byte_component [%lu]\n", ecs_id(name))
