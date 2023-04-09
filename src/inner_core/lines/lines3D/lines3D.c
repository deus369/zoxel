#ifndef zoxel_lines3D
#define zoxel_lines3D

// 0 | EcsOnStore
long int line3D_render_system_id;
zoxel_declare_tag(Line3D)
zoxel_component(LineData3D, float6)     //! The two points in a line3D.
#include "prefabs/line3D.c"
#include "shaders/line3D_shader.c"
#include "systems/line3D_render_system.c"
#include "util/test_lines3D.c"

zoxel_begin_module(Lines3D)
zoxel_define_tag(Line3D)
zoxel_define_component(LineData3D)
if (!headless) {
    initialize_shader_line3D();
    zoxel_system_1(Line3DRenderSystem, 0, [none] Line3D, [in] LineData3D, [in] LineThickness, [in] Color)
    line3D_render_system_id = ecs_id(Line3DRenderSystem);
}
spawn_prefab_line3D(world);
zoxel_end_module(Lines3D)

#endif