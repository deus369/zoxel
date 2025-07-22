#ifndef zox_mod_lines3D
#define zox_mod_lines3D

// should live for .1 seconds
const float line_frame_timing = 1 / 30.0f;
zox_declare_tag(Line3D)
zox_component(LineData3D, float6)     // The two points in a line3D
zox_declare_tag(CubeLines)
zox_component_byte(DebugCubeLines)
zox_component(CubeLinesThickness, float)
#include "prefabs/_.c"
#include "shaders/line3D.c"
#include "util/_.c"
#include "systems/_.c"

void spawn_shaders_lines3D(ecs_world_t *world) {
    if (render_backend == zox_render_backend_opengl) {
        initialize_shader_line3D(world);
    }
}

void spawn_prefabs_lines3D(ecs_world_t *world) {
    spawn_prefab_line3D(world);
    spawn_prefab_temporary_line3D(world);
    spawn_prefab_cube_lines(world);
}

zox_begin_module(Lines3D)
    zox_define_tag(Line3D)
    zox_define_tag(CubeLines)
    zox_define_component(DebugCubeLines)
    zox_define_component(LineData3D)
    zox_define_component(CubeLinesThickness)
    define_systems_lines3(world);
    add_hook_load_shader(&spawn_shaders_lines3D);
    spawn_prefabs_lines3D(world);
zox_end_module(Lines3D)

#endif