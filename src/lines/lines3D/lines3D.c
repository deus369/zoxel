#ifndef zox_mod_lines3D
#define zox_mod_lines3D

zox_declare_tag(Line3D)
zox_component(LineData3D, float6)     // The two points in a line3D
zox_declare_tag(CubeLines)
zox_component_byte(DebugCubeLines)
zox_component(CubeLinesThickness, float)
#include "prefabs/_.c"
#include "shaders/line3D.c"
#include "systems/line3D_render_system.c"
#include "systems/cube_line_render_system.c"
#include "util/_.c"

void spawn_shaders_lines3D(ecs_world_t *world) {
    if (!is_using_vulkan) initialize_shader_line3D();
}

void spawn_prefabs_lines3D(ecs_world_t *world) {
    spawn_prefab_line3D(world);
    spawn_prefab_temporary_line3D(world);
    spawn_prefab_cube_lines(world);
}

zox_begin_module(Lines3D)
    add_hook_load_shader(&spawn_shaders_lines3D);
    zox_define_tag(Line3D)
    zox_define_tag(CubeLines)
    zox_define_component(DebugCubeLines)
    zox_define_component(LineData3D)
    zox_define_component(CubeLinesThickness)
    zox_render3D_plus_system(Line3DRenderSystem,
        [in] LineData3D,
        [in] lines.LineThickness,
        [in] colorz.ColorRGB,
        [none] Line3D)
    // todo: make overlay layer in render stack
    zox_render3D_plus_system(CubeLineRenderSystem,
        [none] CubeLines,
        [in] DebugCubeLines,
        [in] CubeLinesThickness,
        [in] colorz.ColorRGB,
        [in] transforms3.d.Position3D,
        [in] transforms3.d.Rotation3D,
        [in] generic.Bounds3D,
        [in] rendering.RenderLod,
        [in] rendering.RenderDisabled)
    spawn_prefabs_lines3D(world);
zox_end_module(Lines3D)

#endif