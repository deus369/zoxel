#define zox_pip_a EcsOnLoad
#define zox_pip_b EcsPostLoad
#define zox_pip_c EcsPreUpdate
#define zox_pip_d EcsOnUpdate
#define zox_pip_e EcsOnValidate
#define zox_pip_f EcsPostUpdate
#define zox_pip_g EcsPreStore
#define zox_pip_h EcsOnStore

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