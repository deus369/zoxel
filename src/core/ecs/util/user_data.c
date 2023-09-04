#define zox_declare_user_data(name)\
    zox_declare_tag(name)\
    zox_declare_tag(User##name)\
    zox_memory_component(User##name##s, ecs_entity_t)

#define zox_define_user_data(name)\
    zox_define_tag(name)\
    zox_define_tag(User##name)\
    zox_define_memory_component(User##name##s)
