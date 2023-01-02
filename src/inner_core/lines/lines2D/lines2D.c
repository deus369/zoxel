#ifndef zoxel_lines2D
#define zoxel_lines2D

// tags
zoxel_declare_tag(Line2D)
// components
//! The two points in a line2D.
zoxel_component(LineData2D, float4)
//! The two ui points in a line2D.
zoxel_component(LineElementData, int4)
// prefabs
#include "prefabs/line2D.c"
#include "prefabs/ui_line2D.c"
// systems
#include "systems/line2D_element_system.c"
#include "systems/line2D_render_system.c"

//! Lines2D Module.
void Lines2DImport(ecs_world_t *world)
{
    zoxel_module(Lines2D)
    zoxel_define_tag(Line2D)
    zoxel_define_component(LineData2D)
    zoxel_define_component(LineElementData)
    // systems
    zoxel_filter(line2Ds_query, world,
        [none] Line2D, [in] LineElementData, [none] CanvasLink, [none] LineData2D);
    zoxel_system_ctx(world, Line2DElementSystem, EcsPreUpdate, line2Ds_query,
        [none] Line2D, [in] LineElementData, [in] CanvasLink, [out] LineData2D);
    if (!headless)
    {
        initialize_shader_line2D();
        zoxel_system_main_thread(world, Line2DRenderSystem, EcsOnStore, // 0
            [none] Line2D, [in] LineData2D, [in] LineThickness, [in] Color);
    }
    // prefabs
    spawn_prefab_line2D(world);
    spawn_prefab_ui_line2D(world);
    // testing
    /*float line_length = 1.0f;
    spawn_line2D(world, (float2) { -line_length, 0 }, (float2) { line_length, 0 }, 3.0f);
    spawn_line2D(world, (float2) { -line_length, -line_length }, (float2) { -line_length, line_length }, 6.0f);*/
    // spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { 1920, 1080 }, 6.0f, 0);
}
#endif