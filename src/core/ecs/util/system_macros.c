//! A bunch of flecs system macros

#define main_thread_pipeline EcsOnStore

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
// the idea is to move the element before the ui is raycasted
// mouse exact - outside loop before it
// mouse drag - DraggerEndSystem - EcsOnLoad
// ElementDragSystem - EcsPostLoad
// position ui children - ElementPositionSystem - EcsPreUpdate
// raycast new positioned ones - ElementRaycastSystem - EcsOnUpdate
// respond to raycasting ui - EcsOnValidate
// respond to click events - WindowCloseSystem - EcsPostUpdate
//! Used to respond to first level events.
// #define zoxel_event_respond_system_main_thread(system_name, tag_name, event_component_name) zox_system_1(system_name, EcsPreStore, [out] tag_name, [in] event_component_name);

#define zox_declare_system(name) ECS_SYSTEM_DECLARE(name);

// adds multithreading
#define zox_system(id_, phase, ...) {\
    ecs_system_desc_t desc = {0};\
    ecs_entity_desc_t edesc = {0};\
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0);\
    edesc.add[1] = (phase);\
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__;\
    desc.callback = id_;\
    desc.multi_threaded = 1;\
    ecs_id(id_) = ecs_system_init(world, &desc);\
}
// ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);

#define zox_system_1(id_, phase, ...) {\
    ecs_system_desc_t desc = {0};\
    ecs_entity_desc_t edesc = {0};\
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0);\
    edesc.add[1] = (phase);\
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__;\
    desc.callback = id_;\
    desc.multi_threaded = 0;\
    ecs_id(id_) = ecs_system_init(world, &desc);\
}

#define zox_render2D_system(name, ...) {\
    zox_system_1(name, 0, __VA_ARGS__)\
    add_to_render2D_loop(ecs_id(name));\
}

#define zox_render3D_system(name, ...) {\
    if (!headless) {\
        zox_system_1(name, 0, __VA_ARGS__)\
        add_to_render3D_loop(ecs_id(name));\
    }\
}

// ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);

//! Multithreaded System Definitions
#define zox_system_ctx(id_, phase, ctx_, ...) {\
    ecs_system_desc_t desc = {0};\
    ecs_entity_desc_t edesc = {0};\
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0);\
    edesc.add[1] = (phase);\
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__; \
    desc.callback = id_;\
    desc.multi_threaded = 1;\
    desc.ctx = ctx_; \
    ecs_id(id_) = ecs_system_init(world, &desc);\
}

// ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);

#define zox_system_ctx_1(id_, phase, ctx_, ...) {\
    ecs_system_desc_t desc = {0};\
    ecs_entity_desc_t edesc = {0};\
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0);\
    edesc.add[1] = (phase);\
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__;\
    desc.callback = id_;\
    desc.ctx = ctx_;\
    ecs_id(id_) = ecs_system_init(world, &desc);\
}

// ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);

#define zox_texture_generation_system(texture_tag, system) {\
    zox_filter(generateTextureQuery, [none] texture_tag, [out] GenerateTexture)\
    zox_system_ctx(system, EcsPostUpdate, generateTextureQuery, [none] texture_tag, [out] TextureDirty, [out] TextureData, [in] TextureSize, [out] GenerateTexture)\
}

#define zox_texture_generation_system2(texture_tag, system, ...) {\
    zox_filter(generateTextureQuery, [none] texture_tag, [out] GenerateTexture)\
    zox_system_ctx(system, EcsPostUpdate, generateTextureQuery, [none] texture_tag, [out] TextureDirty, [out] TextureData, [in] TextureSize, [out] GenerateTexture, __VA_ARGS__)\
}

// EcsOnStore
#define zox_define_reset_system(system_name, component_name) zox_system(system_name, EcsPreStore, [out] component_name)

#define zox_reset_system(system_name, component_name)\
void system_name(ecs_iter_t *it) {\
    component_name *components = ecs_field(it, component_name, 1);\
    for (int i = 0; i < it->count; i++) {\
        component_name *component = &components[i];\
        if (component->value == 1) component->value = 0;\
    }\
} zox_declare_system(system_name)

// because these don't work in multithreading
// zox_system_1
// if (!ecs_query_changed(NULL, it)) return;
// ecs_query_skip(it);

// #define zoxel_button_system(system, tag) zox_system(system, EcsPostUpdate, [none] tag, [in] ClickState);
// #define zoxel_button_system2(system, tag, pipeline) zox_system(system, pipeline, [none] tag, [in] ClickState);

// used for systems

#define zox_iter_world() ecs_world_t *world = it->world;

#define zox_field_in(component_name, field_name, index) const component_name *field_name = ecs_field(it, component_name, index);

#define zox_field_out(component_name, field_name, index) component_name *field_name = ecs_field(it, component_name, index);

#define zox_field_i_in(component_name, field_name, variable_name) const component_name *variable_name = &field_name[i];

#define zox_field_i_out(component_name, field_name, variable_name) component_name *variable_name = &field_name[i];

#define zox_field_e() const ecs_entity_t e = it->entities[i];
