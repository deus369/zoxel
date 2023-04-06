//! A bunch of flecs system macros.


/**
Chose one pipeline tag for each type of system.
    EcsOnLoad
    EcsPostLoad
    EcsPreUpdate
    EcsOnUpdate
    EcsOnValidate
    EcsPostUpdate
    EcsPreStore
    EcsOnStore
*/

#define zoxel_declare_system(name) ECS_SYSTEM_DECLARE(name);

//! Multithreaded System Definitions.
#define zoxel_system(id_, phase, ...) { \
    ecs_system_desc_t desc = {0}; \
    ecs_entity_desc_t edesc = {0}; \
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0); \
    edesc.add[1] = (phase); \
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__; \
    desc.callback = id_; \
    desc.multi_threaded = 1; \
    ecs_id(id_) = ecs_system_init(world, &desc); \
} \
ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);

#define zoxel_system_main_thread(world, id_, phase, ...) { \
    ecs_system_desc_t desc = {0}; \
    ecs_entity_desc_t edesc = {0}; \
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0); \
    edesc.add[1] = (phase); \
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__; \
    desc.callback = id_; \
    ecs_id(id_) = ecs_system_init(world, &desc); \
} \
ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);


//! Multithreaded System Definitions.
#define zoxel_system_ctx(world, id_, phase, ctx_, ...) { \
    ecs_system_desc_t desc = {0}; \
    ecs_entity_desc_t edesc = {0}; \
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0); \
    edesc.add[1] = (phase); \
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__; \
    desc.callback = id_; \
    desc.multi_threaded = 1; \
    desc.ctx = ctx_; \
    ecs_id(id_) = ecs_system_init(world, &desc); \
} \
ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);

#define zoxel_system_ctx_main_thread(world, id_, phase, ctx_, ...) { \
    ecs_system_desc_t desc = {0}; \
    ecs_entity_desc_t edesc = {0}; \
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0); \
    edesc.add[1] = (phase); \
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__; \
    desc.callback = id_; \
    desc.ctx = ctx_; \
    ecs_id(id_) = ecs_system_init(world, &desc); \
} \
ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);

/*
#define ZOXEL_SYSTEM_MULTITHREADED_CTX2(world, id_, phase, ctx1, ctx2, ...) { \
    ecs_system_desc_t desc = {0}; \
    ecs_entity_desc_t edesc = {0}; \
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0); \
    edesc.add[1] = (phase); \
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__; \
    desc.callback = id_; \
    desc.multi_threaded = 1; \
    QueryContainer2 *queryContainer2 = & (QueryContainer2) { ctx1, ctx2 }; \
    desc.ctx = queryContainer2; \
    ecs_id(id_) = ecs_system_init(world, &desc); \
} \
ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);
*/

#define zoxel_texture_generation_system(texture_tag, system) {\
    zoxel_filter(generateTextureQuery, world, [none] texture_tag, [in] GenerateTexture);\
    zoxel_system_ctx(world, system, EcsOnUpdate, generateTextureQuery,\
        [none] texture_tag, [out] TextureDirty, [out] Texture, [in] TextureSize, [in] GenerateTexture);\
}

#define zoxel_button_system(system, tag) zoxel_system(system, EcsPostUpdate, [none] tag, [in] ClickableState);

#define zoxel_button_system2(system, tag, pipeline) zoxel_system(system, pipeline, [none] tag, [in] ClickableState);

// EcsPreFrame, EcsOnLoad, EcsPostLoad, EcsPreUpdate, EcsOnUpdate
    
#define zoxel_reset_system(system_name, component_name)\
void system_name(ecs_iter_t *it) {\
    if (!ecs_query_changed(NULL, it)) {\
        return;\
    }\
    ecs_query_skip(it);\
    component_name *components = ecs_field(it, component_name, 1);\
    for (int i = 0; i < it->count; i++) {\
        component_name *component = &components[i];\
        if (component->value == 1) {\
            component->value = 0;\
        }\
    }\
}\
ECS_SYSTEM_DECLARE(system_name);

//! Used at the end to reset systems.
#define zoxel_define_reset_system(system_name, component_name)\
    zoxel_system_main_thread(world, system_name, EcsOnStore, [out] component_name);

// the idea is to move the element before the ui is raycasted
// mouse exact - outside loop before it
// mouse drag - DraggerEndSystem - EcsOnLoad
// HeaderDragSystem - EcsPostLoad
// position ui children - ElementPositionSystem - EcsPreUpdate
// raycast new positioned ones - ElementRaycastSystem - EcsOnUpdate
// respond to raycasting ui - EcsOnValidate
// respond to click events - WindowCloseSystem - EcsPostUpdate

//! Used to respond to first level events.
#define zoxel_event_respond_system_main_thread(system_name, tag_name, event_component_name)\
    zoxel_system_main_thread(world, system_name, EcsPreStore, [out] tag_name, [in] event_component_name);

