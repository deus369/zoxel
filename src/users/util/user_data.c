#define zoxc_userdata(T) \
    zox_tag(T); \
    zoxc_entities(T##Links) \
    zoxc_entity(T##Link)

#define zoxd_userdata(T) \
    zox_define_tag(T); \
    zox_define_entities_component(T##Links); \
    zox_define_component_entity(T##Link)

// macro for creating prefab data for user data
#define zoxf_user_prefabs(T, name, label)\
    ecs_entity_t prefab_##name;\
    \
    ecs_entity_t spawn_prefab_##name(ecs_world_t *world) {\
        zox_prefab()\
        zox_prefab_name(label)\
        zox_add_tag(e, T)\
        zox_prefab_add(e, ZoxName)\
        zox_prefab_set(e, UserLink, { 0 })\
        zox_prefab_set(e, TextureLink, { 0 })\
        prefab_##name = e;\
        return e;\
    }\
    \
    /* generic meta spawn function*/\
    ecs_entity_t spawn_meta_##name( \
        ecs_world_t *world, \
        const ecs_entity_t prefab, \
        const char *name \
    ) {\
        zox_prefab_child(prefab)\
        zox_set_name(e, name)\
        ZoxName *zoxName = &((ZoxName) { 0, NULL });\
        set_zox_name(zoxName, name);\
        zox_set(e, ZoxName, { zoxName->length, zoxName->value })\
        return e;\
    }\
    \
    ecs_entity_t spawn_meta_##name##_zox_name( \
        ecs_world_t *world, \
        const ecs_entity_t prefab, \
        const ZoxName *name \
    ) {\
        zox_prefab_child(prefab)\
        zox_name("meta_"label)\
        ZoxName *zoxName = &((ZoxName) { 0, NULL });\
        clone_ZoxName(zoxName, name);\
        zox_set(e, ZoxName, { zoxName->length, zoxName->value })\
        return e;\
    }\
    \
    ecs_entity_t spawn_user_##name( \
        ecs_world_t *world, \
        ecs_entity_t prefab, \
        ecs_entity_t user \
    ) {\
        zox_instance(prefab)\
        zox_name(zox_get_name(prefab))\
        zox_set(e, UserLink, { user })\
        return e;\
    }
