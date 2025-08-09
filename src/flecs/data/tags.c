//! A bunch of flecs system macros
// todo: make all use of these pipeline tags, zox_ ones because it
//  > makes it easier to organize
// breaks visuals if i put on store

#define zoxp_transforms EcsPostUpdate // for Transforms
#define zoxp_mainthread EcsPreStore // EcsPreStore | EcsOnStore
#define zoxp_textures EcsOnUpdate // EcsPostUpdate