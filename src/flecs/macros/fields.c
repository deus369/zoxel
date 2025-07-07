#define zox_field_world()\
    ecs_world_t *world = it->world;

#define zox_field_in(component_name, name, index)\
    const component_name *name = ecs_field(it, component_name, index);

#define zox_field_out(component_name, name, index)\
    component_name *name = ecs_field(it, component_name, index);

#define zox_field_in_iter(iter, component_name, name, index)\
    const component_name *name = ecs_field(iter, component_name, index);

#define zox_field_out_iter(iter, component_name, name, index)\
    component_name *name = ecs_field(iter, component_name, index);

#define zox_field_i(component_name, field_name, variable_name)\
    const component_name *variable_name = &field_name[i];

#define zox_field_o(component_name, field_name, variable_name)\
    component_name *variable_name = &field_name[i];

#define zox_field_e()\
    const ecs_entity_t e = it->entities[i];


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