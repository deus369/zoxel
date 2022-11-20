#ifndef zoxel
#define zoxel

// =-= Flecs =-=
#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM 
#define FLECS_PIPELINE
//! Use these when profiling.
// #define FLECS_REST
// #define FLECS_MONITOR
#include "../imports/flecs.h"

// SDL
#define SDL_IMAGES

// -- Tests / Options --
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

// =-= Zoxel =-=
#include "core/core.c"
#include "inner_core/inner_core.c"
#include "outer_core/outer_core.c"
#include "gameplay/gameplay.c"
#include "space/space.c"

void ZoxelImport(ecs_world_t *world)
{
    ECS_MODULE(world, Zoxel);
    ECS_IMPORT(world, Core);
    ECS_IMPORT(world, InnerCore);
    ECS_IMPORT(world, OuterCore);
    ECS_IMPORT(world, Gameplay);
    ECS_IMPORT(world, Space);
}
#endif