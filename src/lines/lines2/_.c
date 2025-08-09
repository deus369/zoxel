#ifndef zoxm_lines2D
#define zoxm_lines2D

zox_tag(Line2D);
zox_tag(ElementLine2D);
zoxc(LineData2D, float4);
zoxc(LinePosition2D, int4);
zoxc(LineLocalPosition2D, int4);
zoxc(LineAnchor, float4);
#include "shaders/line2D.c"
#include "util/line_util.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Lines2D)
    zox_define_tag(Line2D);
    zox_define_tag(ElementLine2D);
    zox_define_component(LineData2D);
    zox_define_component(LinePosition2D);
    zox_define_component(LineLocalPosition2D);
    zox_define_component(LineAnchor);
    define_systems_line2D(world);
    add_hook_load_shader(&spawn_shader_line2D);
    add_hook_spawn_prefabs(spawn_prefabs_lines2D);
zox_end_module(Lines2D)

#endif