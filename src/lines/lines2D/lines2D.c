#ifndef zox_mod_lines2D
#define zox_mod_lines2D

zox_declare_tag(Line2D)
zox_declare_tag(ElementLine2D)  // lines in ui
zox_component(LineData2D, float4)       // The two points in a line2D
zox_component(LinePosition2D, int4)     // The two ui points in a line2D
zox_component(LineLocalPosition2D, int4)
zox_component(LineAnchor, float4)
#include "shaders/line2D.c"
#include "util/line_util.c"
#include "prefabs/_.c"
#include "systems/line2D_element_system.c"
#include "systems/line2D_render_system.c"
#include "util/canvas_lines.c"
#include "util/grid2D.c"

void spawn_shaders_lines2D(ecs_world_t *world) {
    if (render_backend == zox_render_backend_opengl) {
        initialize_shader_line2D(world);
    }
}

zox_begin_module(Lines2D)
    zox_define_tag(Line2D)
    zox_define_tag(ElementLine2D)
    zox_define_component(LineData2D)
    zox_define_component(LinePosition2D)
    zox_define_component(LineLocalPosition2D)
    zox_define_component(LineAnchor)
    zox_system(Line2DElementSystem, zox_pipelines_pre_render,
        [in] LinePosition2D,
        [in] elements.core.CanvasLink,
        [out] LineData2D,
        [none] Line2D)
    zox_render3D_system(Line2DRenderSystem,
        [in] LineData2D,
        [in] lines.LineThickness,
        [in] colorz.Color,
        [in] elements.core.Layer2D,
        [none] Line2D,
        [none] !ElementLine2D)
    zox_render2D_system(ElementLine2DRenderSystem,
        [in] LineData2D,
        [in] lines.LineThickness,
        [in] colorz.Color,
        [in] elements.core.Layer2D,
        [none] Line2D,
        [none] ElementLine2D)
    add_hook_load_shader(&spawn_shaders_lines2D);
    spawn_prefabs_lines2D(world);
zox_end_module(Lines2D)

#endif
