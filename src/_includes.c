// =-= Flecs =-=
#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM 
#define FLECS_PIPELINE
//! Use these when profiling.
// #define FLECS_REST
// #define FLECS_MONITOR
#include "../include/flecs.h"

// Platforms
#if defined(__unix__) && __ANDROID__
    #define ANDROID_BUILD
#endif
#ifdef __EMSCRIPTEN__
    #define WEB_BUILD
#endif

// SDL
#define SDL_IMAGES
#define SDL_MIXER
// #define USE_SDL_3

// -- Tests / Options --
// #define zoxel_test_character2Ds
// #define zoxel_test_cubes             // Failing atm, gl error at opengl_draw_triangles
// #define zoxel_test_cubes_textured    // wip
// #define zoxel_test_character3Ds      // todo
#define zoxel_test_voxels
#define zoxel_test_voxels_terrain
// #define zoxel_test_uis
// -- debugs --
//! \todo Fix pathing for android, cannot get resources there.
// #define zoxel_debug_pathing 
// #define zoxel_debug_prefabs
// #define zoxel_debug_spawns
// #define zoxel_debug_sdl
// #define zoxel_debug_opengl
// #define zoxel_catch_opengl_errors
// #define debug_viewport_resize
// #define zoxel_debug_element_raycasting
// #define debug_ui_positioning
// #define debug_ui_scaling
// #define zoxel_time_render_loop

#include "zoxel_engine.c"
#include "zoxel/zoxel.c"