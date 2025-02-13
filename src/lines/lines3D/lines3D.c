#ifndef zox_mod_lines3D
#define zox_mod_lines3D

zox_declare_tag(Line3D)
zox_component(LineData3D, float6)     // The two points in a line3D
zox_declare_tag(CubeLines)
zox_component_byte(DebugCubeLines)
zox_component(CubeLinesThickness, float)
#include "prefabs/line3D.c"
#include "prefabs/temporary_line3D.c"
#include "prefabs/cube_lines.c"
#include "shaders/line3D.c"
#include "systems/line3D_render_system.c"
#include "systems/cube_line_render_system.c"
#include "util/terrain_grid.c"

void add_debug_cube(ecs_world_t *world, const ecs_entity_t e, const float size) {
    zox_prefab_set(e, DebugCubeLines, { 1 })
    zox_add_tag(e, CubeLines)
    zox_prefab_set(e, CubeLinesThickness, { 4 })
    zox_prefab_set(e, ColorRGB, {{ 0, 255, 255 }})
    zox_prefab_set(e, Bounds3D, {{ size, size, size }})
    zox_prefab_set(e, RenderLod, { 0 })
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_add(e, MeshIndicies)
}

void spawn_shaders_lines3D(ecs_world_t *world) {
    if (!is_using_vulkan) initialize_shader_line3D();
}

void spawn_prefabs_lines3D(ecs_world_t *world) {
    spawn_prefab_line3D(world);
    spawn_prefab_temporary_line3D(world);
    spawn_prefab_cube_lines(world);
}

zox_begin_module(Lines3D)
    add_load_shader_function(&spawn_shaders_lines3D);
    zox_define_tag(Line3D)
    zox_define_tag(CubeLines)
    zox_define_component(DebugCubeLines)
    zox_define_component(LineData3D)
    zox_define_component(CubeLinesThickness)
    zox_render3D_plus_system(Line3DRenderSystem, [in] LineData3D, [in] LineThickness, [in] ColorRGB, [none] Line3D)
    // todo: make overlay layer in render stack
    zox_render3D_system(CubeLineRenderSystem, [none] CubeLines, [in] DebugCubeLines, [in] CubeLinesThickness, [in] ColorRGB, [in] Position3D, [in] Rotation3D, [in] Bounds3D, [in] RenderLod, [in] RenderDisabled)
    spawn_prefabs_lines3D(world);
zox_end_module(Lines3D)

#endif
