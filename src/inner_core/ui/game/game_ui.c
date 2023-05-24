#ifndef zoxel_game_ui
#define zoxel_game_ui

zox_declare_tag(MainMenu)
zox_declare_tag(OptionsUI)
zox_declare_tag(PauseUI)
zox_declare_tag(FPSDisplay)
zox_declare_tag(QuadsCountLabel)
zox_component(FPSDisplayTicker, double)
#include "fun/button_event_play_game.c"
#include "fun/button_event_exit_game.c"
#include "fun/button_event_return_to_game.c"
#include "prefabs/main_menu.c"
#include "prefabs/fps_display.c"
#include "prefabs/pause_ui.c"
#include "prefabs/options_ui.c"
#include "prefabs/quad_count_label.c"
#include "systems/fps_display_system.c"
#include "systems/quads_display_system.c"

zox_begin_module(GameUI)
zox_define_tag(MainMenu)
zox_define_tag(OptionsUI)
zox_define_tag(PauseUI)
zox_define_tag(FPSDisplay)
zox_define_tag(QuadsCountLabel)
zox_define_component(FPSDisplayTicker)
zox_system(FpsDisplaySystem, EcsPreUpdate, [out] FPSDisplayTicker, [out] ZextDirty, [out] ZextData)
zox_system(QuadsLabelSystem, EcsPreUpdate, [none] QuadsCountLabel, [out] ZextDirty, [out] ZextData)
spawn_prefab_main_menu(world);
spawn_prefab_fps_display(world);
spawn_prefab_pause_ui(world);
spawn_prefab_options_ui(world);
spawn_prefab_quad_count_label(world);
zoxel_end_module(GameUI)

// todo: fps display to be multithreaded

#endif