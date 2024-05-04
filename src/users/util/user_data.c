#define zox_declare_user_data(Name)\
zox_declare_tag(Name)\
zox_memory_component(User##Name##s, ecs_entity_t)\
zox_entities_component(Name##Links)\
zox_component_entity(Name##Link)

#define zox_define_user_data(Name)\
zox_define_tag(Name)\
zox_define_memory_component(User##Name##s)\
zox_define_entities_component(Name##Links)\
zox_define_component_entity(Name##Link)

#define zox_create_user_data_prefabs(Name, name, label)\
ecs_entity_t prefab_##name;\
\
void spawn_prefab_##name(ecs_world_t *world) {\
    zox_prefab()\
    zox_prefab_name(label)\
    zox_add_tag(e, Name)\
    zox_prefab_set(e, UserLink, { 0 })\
    /*zox_prefab_set(e, ZoxName, { 0, NULL })*/\
    prefab_##name = e;\
}\
\
ecs_entity_t spawn_meta_##name(ecs_world_t *world, const char *name) {\
    zox_prefab_child(prefab_##name)\
    zox_prefab_name("meta_"label)\
    /* shared variables for all meta data */\
    zox_set(e, ZoxName, { 0, NULL })\
    ZoxName *zoxName = zox_get_mut(e, ZoxName)\
    set_zox_name(zoxName, name);\
    zox_modified(e, ZoxName)\
    return e;\
}\
\
ecs_entity_t spawn_user_##name(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t user) {\
    zox_instance(prefab)\
    /*zox_name("user_"label)*/\
    zox_set(e, UserLink, { user })\
    return e;\
}
