#define zox_declare_user_data(Name)\
zox_declare_tag(Name)\
/*zox_memory_component(User##Name##s, ecs_entity_t)*/\
zox_entities_component(Name##Links)\
zox_component_entity(Name##Link)

#define zox_define_user_data(Name)\
zox_define_tag(Name)\
/*zox_define_memory_component(User##Name##s)*/\
zox_define_entities_component(Name##Links)\
zox_define_component_entity(Name##Link)

// macro for creating prefab data for user data
#define zox_create_user_data_prefabs(Name, name, label)\
ecs_entity_t prefab_##name;\
\
ecs_entity_t spawn_prefab_##name(ecs_world_t *world) {\
    zox_prefab()\
    zox_prefab_name(label)\
    zox_add_tag(e, Name)\
    zox_prefab_add(e, ZoxName)\
    zox_prefab_set(e, UserLink, { 0 })\
    zox_prefab_set(e, TextureLink, { 0 })\
    prefab_##name = e;\
    return e;\
}\
\
/* generic meta spawn function*/\
ecs_entity_t spawn_meta_##name(ecs_world_t *world, const ecs_entity_t prefab, const char *name) {\
    zox_prefab_child(prefab)\
    zox_set_name(e, name)\
    ZoxName *zoxName = &((ZoxName) { 0, NULL });\
    set_zox_name(zoxName, name);\
    zox_set(e, ZoxName, { zoxName->length, zoxName->value })\
    return e;\
}\
\
ecs_entity_t spawn_meta_##name##_zox_name(ecs_world_t *world, const ecs_entity_t prefab, const ZoxName *name) {\
    zox_prefab_child(prefab)\
    zox_name("meta_"label)\
    ZoxName *zoxName = &((ZoxName) { 0, NULL });\
    clone_ZoxName(zoxName, name);\
    zox_set(e, ZoxName, { zoxName->length, zoxName->value })\
    return e;\
}\
\
ecs_entity_t spawn_user_##name(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t user) {\
    zox_instance(prefab)\
    zox_name(zox_get_name(prefab))\
    zox_set(e, UserLink, { user })\
    return e;\
}
