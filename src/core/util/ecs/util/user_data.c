#define zoxel_declare_user_data(name)\
    zoxel_declare_tag(name)\
    zoxel_declare_tag(User##name)\
    zoxel_memory_component(User##name##s, ecs_entity_t)

#define zoxel_define_user_data(name)\
    zoxel_define_tag(name)\
    zoxel_define_tag(User##name)\
    zoxel_define_memory_component(User##name##s)
