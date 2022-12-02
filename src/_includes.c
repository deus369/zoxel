// =-= Flecs =-=
#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM 
#define FLECS_PIPELINE
//! Use these when profiling.
// #define FLECS_REST
// #define FLECS_MONITOR
#include "../includes/flecs.h"

// SDL
#define SDL_IMAGES
// #define SDL_MIXER
//#define USE_SDL_3

// -- Tests / Options --
// queue lengths
#define maxMeshQueue 4096
#define maxTextureQueue 4096
// #define zoxel_test_character2Ds
#define zoxel_test_cubes
// #define zoxel_test_cubes_textured    // wip
// #define zoxel_test_character3Ds      // todo
#define zoxel_test_voxels
#define zoxel_test_voxels_terrain       // uvs - wip
// #define zoxel_test_uis
// -- debugs --
// #define zoxel_debug_prefabs
// #define zoxel_debug_spawns
// #define zoxel_debug_sdl
// #define zoxel_debug_opengl
// #define zoxel_debug_pathing
// #define zoxel_catch_opengl_errors
// #define debug_viewport_resize
// #define zoxel_debug_element_raycasting
// #define debug_ui_positioning
// #define debug_ui_scaling
// #define zoxel_time_render_loop

#include "zoxel_engine.c"
#include "zoxel/zoxel.c"