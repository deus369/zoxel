// =-= Flecs =-=
#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM 
#define FLECS_PIPELINE
//! Use these when profiling >
//  make dev && make run-dev-profiler
//  go to https://www.flecs.dev/explorer/
// #define FLECS_REST
// #define FLECS_MONITOR
// finally our flecs
#include "../include/flecs/flecs.h"

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
#define zoxel_test_chickens
// #define zoxel_test_character3Ds
// #define disable_voxel_left
// #define disable_voxel_right
// #define disable_voxel_back
// #define disable_voxel_front
// #define disable_voxel_down
// #define zoxel_disable_close_nodes
// #define zoxel_test_lines3D
// #define zoxel_test_networking
// #define zoxel_test_brain
// #define zoxel_test_character2Ds
// #define zoxel_test_cubes             // Failing atm, gl error at opengl_draw_triangles
// #define zoxel_test_cubes_textured    // wip
// #define zoxel_test_character3Ds      // todo
// #define zoxel_test_voxels
// #define zoxel_test_uis

// -- debugs --
// #define zox_logs // add logs with printf
// #define zoxel_catch_opengl_errors
// #define zoxel_log_frames_per_second
// #define zoxel_debug_vox_read
//! \todo Fix pathing for android, cannot get resources there.
// #define zoxel_debug_pathing 
// #define zoxel_debug_prefabs
// #define zoxel_debug_spawns
// #define debug_element_position_change_query
// #define zoxel_debug_sdl
// #define zoxel_debug_opengl
// #define debug_viewport_resize
// #define zoxel_debug_element_raycasting
// #define debug_ui_positioning
// #define debug_ui_scaling
// #define zoxel_time_render_loop

// voxels
#define voxel_octrees
#define zoxel_test_voxels_terrain
// #define zoxel_voxel_disable_distance_division
#define voxels_disable_streaming

// audio
// #define zoxel_debug_sounds
// #define zoxel_debug_music
// #define zoxel_log_sound_generation
// #define zoxel_log_music_playing
// #define zoxel_slow_music
#define zoxel_disable_music

// Timings
#define zoxel_time_main_loop
#define zoxel_time_main_loop_cutoff 40
// #define zoxel_time_octree_chunk_uvs_builds_system
// #define zoxel_time_stream_point_system


// Finally include zoxel engine and zoxel
#include "zoxel_engine.c"
#include "zoxel/zoxel.c"