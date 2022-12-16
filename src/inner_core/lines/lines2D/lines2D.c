#ifndef zoxel_lines2D
#define zoxel_lines2D

// tags
ECS_DECLARE(Line2D);
// components
//! The two points in a line, held in a float4.
zoxel_component(LineData2D, float4);
// prefabs
#include "prefabs/line2D.c"
// systems
#include "systems/line2D_render_system.c"

//! Lines2D Module.
void Lines2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Lines2D);
    ECS_TAG_DEFINE(world, Line2D);
    ECS_COMPONENT_DEFINE(world, LineData2D);
    // systems
    zoxel_system_main_thread(world, Line2DRenderSystem, EcsOnStore, // 0
        [none] Line2D, [in] LineData2D, [in] LineThickness);
    // prefabs
    spawn_prefab_line2D(world);
    // testing
    initialize_shader_line2D();
    /*float line_length = 1.0f; // 1.0f / 2.0f;
    spawn_line2D(world, (float2) { -line_length, 0 }, (float2) { line_length, 0 }, 3.0f);
    spawn_line2D(world, (float2) { -line_length, -line_length }, (float2) { -line_length, line_length }, 6.0f);*/
}
#endif