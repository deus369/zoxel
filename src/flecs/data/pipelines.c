//! A bunch of flecs system macros
// todo: make all use of these pipeline tags, zox_ ones because it
//  > makes it easier to organize
// breaks visuals if i put on store

#define zox_pip_a EcsOnLoad
#define zox_pip_b EcsPostLoad
#define zox_pip_c EcsPreUpdate
#define zox_pip_d EcsOnUpdate
#define zox_pip_e EcsOnValidate
#define zox_pip_f EcsPostUpdate
#define zox_pip_g EcsPreStore
#define zox_pip_h EcsOnStore

#define zoxp_update EcsOnUpdate             // normal business here
#define zoxp_mainthread EcsPreStore         // EcsPreStore | EcsOnStore

#define zoxp_inputs_reset EcsOnLoad
#define zoxp_sdl EcsPostLoad
#define zoxp_inputs_enable EcsPreUpdate
#define zoxp_inputs_update EcsOnUpdate
#define zoxp_state_reset EcsPostUpdate


// Data Pipelines
#define zoxp_destroy EcsOnLoad
#define zoxp_voxels_write EcsPostLoad
#define zoxp_textures EcsOnUpdate           // EcsPostUpdate
#define zoxp_voxels_read EcsOnUpdate
#define zoxp_text EcsOnUpdate


// Rendering Pipelines
#define zoxp_physics EcsOnValidate          // EcsOnUpdate
#define zoxp_transforms EcsPostUpdate       // for Transforms
#define zoxp_cameras EcsPreStore            // builds our camera planes, also camera transforms get updated, needs to be post transforms
#define zoxp_pre_render EcsPreStore         // culls renderers basedon those
#define zoxp_rendering EcsOnStore



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