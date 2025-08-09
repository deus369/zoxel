#ifndef zoxm_lines3D
#define zoxm_lines3D

// should live for .1 seconds
const float line_frame_timing = 1 / 30.0f;
zox_tag(Line3D);
zoxc(LineData3D, float6);
zox_tag(CubeLines);
zoxc_byte(DebugCubeLines);
zoxc(CubeLinesThickness, float);
#include "states/_.c"
#include "prefabs/_.c"
#include "shaders/line3D.c"
#include "util/_.c"
#include "systems/_.c"

void spawn_shaders_lines3D(ecs_world_t *world) {
    if (render_backend == zox_render_backend_opengl) {
        initialize_shader_line3D(world);
    }
}

zox_begin_module(Lines3)
    zox_define_tag(Line3D);
    zox_define_tag(CubeLines);
    zox_define_component(DebugCubeLines);
    zox_define_component(LineData3D);
    zox_define_component(CubeLinesThickness);
    define_systems_lines3(world);
    add_hook_load_shader(&spawn_shaders_lines3D);
    add_hook_spawn_prefabs(spawn_prefabs_lines3D);
zox_end_module(Lines3)

#endif