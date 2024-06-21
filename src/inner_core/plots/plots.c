// this is used for visually representing data
#ifndef zox_mod_plots
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
zox_system(PlotLineSystem, EcsOnUpdate, [in] ParentLink, [in] ChildIndex, [out] LineLocalPosition2D, [none] PlotLine)
zox_system(PlotLabelSystem, EcsOnUpdate, [in] ParentLink, [out] ZextDirty, [out] ZextData, [none] PlotLabel)
spawn_prefabs_plots(world);
zoxel_end_module(Plots)

#endif
