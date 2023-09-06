#ifndef zoxel_lines2D
#define zoxel_lines2D

zox_declare_tag(Line2D)
zox_component(LineData2D, float4)     //! The two points in a line2D.
zox_component(LineElementData, int4)  //! The two ui points in a line2D.
#include "prefabs/line2D.c"
#include "prefabs/ui_line2D.c"
#include "prefabs/ui_line2D_temp.c"
#include "systems/line2D_element_system.c"
#include "systems/line2D_render_system.c"

void load_resources_lines2D(ecs_world_t *world) {
    initialize_shader_line2D();
}

void spawn_prefabs_lines2D(ecs_world_t *world) {
    spawn_prefab_line2D(world);
    spawn_prefab_line2D_temp(world);
    spawn_prefab_ui_line2D(world);
    spawn_prefab_ui_line2D_temp(world);
    // testing
    /*float line_length = 1.0f;
    spawn_line2D(world, (float2) { -line_length, 0 }, (float2) { line_length, 0 }, 3.0f, 30);
    spawn_line2D(world, (float2) { -line_length, -line_length }, (float2) { -line_length, line_length }, 6.0f, 30);*/
}

zox_begin_module(Lines2D)
zox_define_tag(Line2D)
zox_define_component(LineData2D)
zox_define_component(LineElementData)
zox_filter(line2Ds_query, [none] Line2D, [in] LineElementData, [none] CanvasLink, [none] LineData2D)
zox_system_ctx(Line2DElementSystem, EcsPreUpdate, line2Ds_query, [none] Line2D, [in] LineElementData, [in] CanvasLink, [out] LineData2D)
if (!headless) {
    zox_system_1(Line2DRenderSystem, 0, [none] Line2D, [in] LineData2D, [in] LineThickness, [in] Color)
    add_to_render2D_loop(ecs_id(Line2DRenderSystem));
}
zoxel_end_module(Lines2D)

// testing
/**/
// spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { 1920, 1080 }, 6.0f, 0);

#endif