// this is used for visually representing data
#if !defined(zoxm_plots) && defined(zoxm_lines2D)
#define zoxm_plots

zox_declare_tag(Plot)
zox_declare_tag(PlotLine)
zox_declare_tag(PlotLabel)
zox_memory_component(PlotDataDouble, double)
zox_component_double(PlotMin)
zox_component_double(PlotMax)
ecs_entity_t prefab_frame_debugger_ui;
#include "prefabs/_.c"
#include "systems/plot_line_system.c"
#include "systems/plot_label_system.c"
#include "systems/plot_limits.c"
#include "util/time.c"

zox_begin_module(Plots)
    zox_define_tag(Plot)
    zox_define_tag(PlotLine)
    zox_define_tag(PlotLabel)
    zox_define_component_double(PlotMin)
    zox_define_component_double(PlotMax)
    zox_define_memory_component(PlotDataDouble)
    zox_system(PlotLineSystem, EcsOnUpdate,
        [in] hierarchys.ParentLink,
        [in] hierarchys.ChildIndex,
        [out] lines2.d.LineLocalPosition2D,
        [none] PlotLine)
    zox_system(PlotLabelSystem, EcsOnUpdate,
        [in] hierarchys.ParentLink,
        [out] texts.ZextDirty,
        [out] texts.TextData,
        [none] PlotLabel);
    zox_system(PlotLimitSystem, EcsOnUpdate,
        [in] PlotDataDouble,
        [out] PlotMin,
        [out] PlotMax,
        [none] Plot);
    spawn_prefabs_plots(world);
zox_end_module(Plots)

#endif