#ifndef zoxel_lines2D
#define zoxel_lines2D

zox_declare_tag(Line2D)
zox_declare_tag(FrameDebugLine)
zox_component(LineData2D, float4)       // The two points in a line2D
zox_component(LinePosition2D, int4)     // The two ui points in a line2D
zox_component(LineLocalPosition2D, int4)
zox_component(LineAnchor, float4)

int4 get_new_line_position(float2 real_position2D, float2 canvas_size_f, float aspect_ratio, int2 parent_position, int4 local_position) {
    int2 new_mid_point = (int2) { ceil((real_position2D.x / aspect_ratio + 0.5f) * canvas_size_f.x), ((real_position2D.y + 0.5f) * canvas_size_f.y) };
    int2 delta = int2_sub(new_mid_point, parent_position);
    int4 output = local_position;
    int4_add_int2(&output, delta);
    return output;
}
// prefabs
#include "prefabs/line2D.c"
#include "prefabs/ui_line2D.c"
#include "prefabs/ui_line2D_temp.c"
#include "prefabs/frame_debugger_ui.c"
// systems
#include "systems/line2D_element_system.c"
#include "systems/line2D_render_system.c"
#include "systems/frame_debug_system.c"
// util
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
    // testing
    /*float line_length = 1.0f;
    spawn_line2D(world, (float2) { -line_length, 0 }, (float2) { line_length, 0 }, 3.0f, 30);
    spawn_line2D(world, (float2) { -line_length, -line_length }, (float2) { -line_length, line_length }, 6.0f, 30);*/
}

void set_line_element_real_position2D(ecs_world_t *world, ecs_entity_t e, float2 real_position2D, int2 canvas_size, int2 parent_position) {
    if (zox_has(e, LinePosition2D)) {
        float2 canvas_size_f = int2_to_float2(canvas_size);
        float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
        const LineLocalPosition2D *lineLocalPosition2D = zox_get(e, LineLocalPosition2D)
        int4 new_line_position = get_new_line_position(real_position2D, canvas_size_f, aspect_ratio, parent_position, lineLocalPosition2D->value);
        LinePosition2D *linePosition2D = zox_get_mut(e, LinePosition2D)
        linePosition2D->value = new_line_position;
        zox_modified(e, LinePosition2D);
    }
}

int2 get_line_element_mid_point(ecs_world_t *world, ecs_entity_t e) {
    if (zox_has(e, LineLocalPosition2D)) {
        const LineLocalPosition2D *lineLocalPosition2D = ecs_get(world, e, LineLocalPosition2D);
        int2 xy_line = int4_xy(lineLocalPosition2D->value);
        int2 pixel_position = int4_zw(lineLocalPosition2D->value);
        int2_subtract(&pixel_position, xy_line);
        int2_divide_int_p(&pixel_position, 2);
        int2_add_p(&pixel_position, xy_line);
        return pixel_position;
    }
    return int2_zero;
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
zox_system_ctx(Line2DElementSystem, EcsPreStore, line2Ds_query, [none] Line2D, [in] LinePosition2D, [in] CanvasLink, [out] LineData2D)
if (!headless) zox_render2D_system(Line2DRenderSystem, [in] LineData2D, [in] LineThickness, [in] Color, [in] Layer2D, [none] Line2D)
zoxel_end_module(Lines2D)

#endif

// zox_set(e, LinePosition2D, { new_line_position })
//int2 new_mid_point = (int2) { ceil((real_position2D.x / aspect_ratio + 0.5f) * canvas_size_f.x), ((real_position2D.y + 0.5f) * canvas_size_f.y) };
//int2 delta = int2_sub(new_mid_point, pixel_position);
// linePosition2D->value = lineLocalPosition2D->value;
// linePosition2D->value = (int4) { new_mid_point.x, new_mid_point.y, new_mid_point.x, new_mid_point.y };
// int4_add_int2(&linePosition2D->value, delta);
// zox_set(e, LinePosition2D, { linePosition2D->value })
// zoxel_log(" > new_mid_point [%ix%i] delta [%ix%i]\n", new_mid_point.x, new_mid_point.y, delta.x, delta.y);
