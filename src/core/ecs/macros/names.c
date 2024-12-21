// #define zox_set_entity_names
#define zox_get_name(e) ecs_get_name(world, e)
#define zox_set_name(e, name) ecs_set_name(world, e, name);
#define zox_get_name_type(type) zox_get_name(ecs_id(type))

