#ifndef zoxel_lines2D
#define zoxel_lines2D

zox_declare_tag(Line2D)
zox_declare_tag(FrameDebugLine)
zox_component(LineData2D, float4)       // The two points in a line2D
zox_component(LinePosition2D, int4)     // The two ui points in a line2D
zox_component(LineLocalPosition2D, int4)
zox_component(LineAnchor, float4)
#include "util/line_util.c"
#include "prefabs/line2D.c"
#include "prefabs/ui_line2D.c"
#include "prefabs/ui_line2D_temp.c"
#include "prefabs/frame_debugger_ui.c"
#include "systems/line2D_element_system.c"
#include "systems/line2D_render_system.c"
#include "systems/frame_debug_system.c"
#include "util/canvas_lines.c"

void initialize_lines2D(ecs_world_t *world) {
    if (!is_using_vulkan) initialize_shader_line2D();
}

void spawn_prefabs_lines2D(ecs_world_t *world) {
    spawn_prefab_line2D(world);
    spawn_prefab_line2D_temp(world);
    spawn_prefab_ui_line2D(world);
    spawn_prefab_ui_line2D_temp(world);
    spawn_prefab_frame_debugger_ui(world);
}

zox_begin_module(Lines2D)
zox_define_tag(Line2D)
zox_define_tag(FrameDebugLine)
zox_define_component(LineData2D)
zox_define_component(LinePosition2D)
zox_define_component(LineLocalPosition2D)
zox_define_component(LineAnchor)
zox_filter(line2Ds_query, [none] Line2D, [in] LinePosition2D, [none] CanvasLink, [none] LineData2D)
zox_system(FrameDebugSystem, EcsOnUpdate, [none] FrameDebugLine, [in] ChildIndex, [out] LineLocalPosition2D)
zox_system_ctx(Line2DElementSystem, zox_pipelines_pre_render, line2Ds_query, [none] Line2D, [in] LinePosition2D, [in] CanvasLink, [out] LineData2D)
if (!headless) zox_render2D_system(Line2DRenderSystem, [in] LineData2D, [in] LineThickness, [in] Color, [in] Layer2D, [none] Line2D)
zoxel_end_module(Lines2D)

#endif
