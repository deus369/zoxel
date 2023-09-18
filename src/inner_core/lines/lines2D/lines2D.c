#ifndef zoxel_lines2D
#define zoxel_lines2D

zox_declare_tag(Line2D)
zox_component(LineData2D, float4)     //! The two points in a line2D.
zox_component(LinePosition2D, int4)  //! The two ui points in a line2D
zox_component(LineLocalPosition2D, int4)

int4 get_new_line_position(float2 real_position2D, float2 canvas_size_f, float aspect_ratio, int2 parent_position, int4 local_position) {
    int2 new_mid_point = (int2) { ceil((real_position2D.x / aspect_ratio + 0.5f) * canvas_size_f.x), ((real_position2D.y + 0.5f) * canvas_size_f.y) };
    int2 delta = int2_sub(new_mid_point, parent_position);
    int4 output = local_position;
    int4_add_int2(&output, delta);
    return output;
}

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

void set_line_element_real_position2D(ecs_world_t *world, ecs_entity_t e, float2 real_position2D, float2 canvas_size_f, float aspect_ratio, int2 parent_position) {
    if (ecs_has(world, e, LinePosition2D)) {
        const LineLocalPosition2D *lineLocalPosition2D = ecs_get(world, e, LineLocalPosition2D);
        int4 new_line_position = get_new_line_position(real_position2D, canvas_size_f, aspect_ratio, parent_position, lineLocalPosition2D->value);
        LinePosition2D *linePosition2D = ecs_get_mut(world, e, LinePosition2D);
        linePosition2D->value = new_line_position;
        ecs_modified(world, e, LinePosition2D);
        // zox_set_only(e, LinePosition2D, { new_line_position })

        //int2 new_mid_point = (int2) { ceil((real_position2D.x / aspect_ratio + 0.5f) * canvas_size_f.x), ((real_position2D.y + 0.5f) * canvas_size_f.y) };
        //int2 delta = int2_sub(new_mid_point, pixel_position);
        // linePosition2D->value = lineLocalPosition2D->value;
        // linePosition2D->value = (int4) { new_mid_point.x, new_mid_point.y, new_mid_point.x, new_mid_point.y };
        // int4_add_int2(&linePosition2D->value, delta);
        // zox_set_only(e, LinePosition2D, { linePosition2D->value })
        // zoxel_log(" > new_mid_point [%ix%i] delta [%ix%i]\n", new_mid_point.x, new_mid_point.y, delta.x, delta.y);
    }
}

int2 get_line_element_mid_point(ecs_world_t *world, ecs_entity_t e) {
    if (ecs_has(world, e, LineLocalPosition2D)) {
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
zox_define_component(LineData2D)
zox_define_component(LinePosition2D)
zox_define_component(LineLocalPosition2D)
zox_filter(line2Ds_query, [none] Line2D, [in] LinePosition2D, [none] CanvasLink, [none] LineData2D)
zox_system_ctx(Line2DElementSystem, EcsPreStore, line2Ds_query, [none] Line2D, [in] LinePosition2D, [in] CanvasLink, [out] LineData2D)
if (!headless) {
    zox_system_1(Line2DRenderSystem, 0, [none] Line2D, [in] LineData2D, [in] LineThickness, [in] Color, [in] Layer2D)
    add_to_render2D_loop(ecs_id(Line2DRenderSystem));
}
zoxel_end_module(Lines2D)

// testing
/**/
// spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { 1920, 1080 }, 6.0f, 0);

#endif