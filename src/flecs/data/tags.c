//! A bunch of flecs system macros
// todo: make all use of these pipeline tags, zox_ ones because it
//  > makes it easier to organize
// breaks visuals if i put on store
#define main_thread_pipeline EcsPreStore // EcsPreStore | EcsOnStore
#define zox_pip_mainthread EcsPreStore // EcsOnStore
#define zox_pipelines_pre_render EcsPreStore
#define zox_pip_textures EcsOnUpdate // EcsPostUpdate

#define zox_pre_store EcsPreStore