#ifndef zoxel_game_ui
#define zoxel_game_ui

zoxel_declare_tag(MainMenu)
zoxel_declare_tag(OptionsUI)
zoxel_declare_tag(PauseUI)
zoxel_declare_tag(FPSDisplay)
zoxel_declare_tag(QuadsCountLabel)
zoxel_component(FPSDisplayTicker, double)
#include "prefabs/main_menu.c"
#include "prefabs/fps_display.c"
#include "prefabs/pause_ui.c"
#include "prefabs/options_ui.c"
#include "prefabs/quad_count_label.c"
#include "systems/fps_display_system.c"
#include "systems/play_game_button_system.c"
#include "systems/exit_game_button_system.c"
#include "systems/quads_display_system.c"

zoxel_begin_module(GameUI)
zoxel_define_tag(MainMenu)
zoxel_define_tag(OptionsUI)
zoxel_define_tag(PauseUI)
zoxel_define_tag(FPSDisplay)
zoxel_define_tag(QuadsCountLabel)
zoxel_define_component(FPSDisplayTicker)
zoxel_system(FpsDisplaySystem, EcsPreUpdate, [out] FPSDisplayTicker, [out] ZextDirty, [out] ZextData)
zoxel_system(QuadsLabelSystem, EcsPreUpdate, [none] QuadsCountLabel, [out] ZextDirty, [out] ZextData)
zoxel_button_system2(PlayGameButtonSystem, elements.PlayGameButton, EcsPreStore)
zoxel_button_system2(ExitGameButtonSystem, elements.ExitGameButton, EcsPreStore)
spawn_prefab_main_menu(world);
spawn_prefab_fps_display(world);
spawn_prefab_pause_ui(world);
spawn_prefab_options_ui(world);
spawn_prefab_quad_count_label(world);
zoxel_end_module(GameUI)

// todo: fps display to be multithreaded

#endif