component_id_list(byte)

#define zox_byte_component(name) zox_component(name, unsigned char)

#define zox_define_component_byte(name)\
ECS_COMPONENT_DEFINE(world, name);\
add_to_ecs_entity_t_array_d(component_ids_byte, ecs_id(name));

// zox_log("   + byte_component [%lu]\n", ecs_id(name))
