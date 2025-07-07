// this is used for visually representing data
#if !defined(zox_mod_plots) && defined(zox_mod_lines2D)
#define zox_mod_plots

ecs_entity_t plot_window_time;
zox_declare_tag(Plot)
zox_declare_tag(PlotLine)
zox_declare_tag(PlotLabel)
zox_memory_component(PlotDataDouble, double)
ecs_entity_t prefab_frame_debugger_ui;
#include "prefabs/plot_window.c"
#include "systems/plot_line_system.c"
#include "systems/plot_label_system.c"
#include "util/time_util.c"

void spawn_prefabs_plots(ecs_world_t *world) {
    prefab_frame_debugger_ui = spawn_prefab_frame_debugger_ui(world);
}

zox_begin_module(Plots)
    zox_define_tag(Plot)
    zox_define_tag(PlotLine)
    zox_define_tag(PlotLabel)
    zox_define_memory_component(PlotDataDouble)
    zox_system(PlotLineSystem, EcsOnUpdate, [in] hierarchys.ParentLink, [in] hierarchys.ChildIndex, [out] lines2.d.LineLocalPosition2D, [none] PlotLine)
    zox_system(PlotLabelSystem, EcsOnUpdate, [in] hierarchys.ParentLink, [out] texts.ZextDirty, [out] texts.TextData, [none] PlotLabel)
    spawn_prefabs_plots(world);
zox_end_module(Plots)

#endif
