#define zox_declare_user_data(Name)\
    zox_declare_tag(Name)\
    zox_declare_tag(User##Name)\
    zox_memory_component(User##Name##s, ecs_entity_t)\
    zox_entities_component(User##Name##Links)\
    zox_entity_component(User##Name##Link)

#define zox_define_user_data(Name)\
    zox_define_tag(Name)\
    zox_define_tag(User##Name)\
    zox_define_memory_component(User##Name##s)\
    zox_define_entities_component(User##Name##Links)\
    zox_define_component(User##Name##Link)

#define zox_create_user_data_prefabs(Name, name, label)\
    ecs_entity_t prefab_user_##name;\
    \
    void spawn_prefab_user_##name(ecs_world_t *world) {\
        ecs_defer_begin(world);\
        zox_prefab()\
        zox_prefab_name("prefab_user_"label)\
        zox_add_tag(e, User##Name)\
        ecs_defer_end(world);\
        prefab_user_##name = e;\
    }\
    \
    ecs_entity_t spawn_user_##name(ecs_world_t *world) {\
        zox_instance(prefab_user_##name)\
        zox_name("user_"label)\
        return e;\
    }
