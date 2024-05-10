#ifndef zoxel_game_ui
#define zoxel_game_ui

#include "settings/settings.c"
zox_declare_tag(MenuMain)
zox_declare_tag(MenuOptions)
zox_declare_tag(MenuPaused)
zox_declare_tag(MenuInGame)
zox_declare_tag(FPSDisplay)
zox_declare_tag(QuadsCountLabel)
zox_declare_tag(GameDebugLabel)
zox_declare_tag(FrameDebuggerWindow)
zox_declare_tag(JoystickUI)
zox_component_int(QuadsCount)
zox_component_double(FPSDisplayTicker)
#include "fun/button_event_play_game.c"
#include "fun/button_event_pause_game.c"
#include "fun/button_event_exit_app.c"
#include "fun/button_event_return_to_game.c"
#include "prefabs/prefabs.c"
#include "systems/fps_display_system.c"
#include "systems/quads_display_system.c"

zox_begin_module(GameUI)
zox_define_tag(MenuMain)
zox_define_tag(MenuOptions)
zox_define_tag(MenuPaused)
zox_define_tag(MenuInGame)
zox_define_tag(FPSDisplay)
zox_define_tag(QuadsCountLabel)
zox_define_tag(GameDebugLabel)

zox_debug_component(GameDebugLabel)
zox_debug_single_module(GameUI)

zox_define_tag(FrameDebuggerWindow)
zox_define_tag(JoystickUI)
zox_define_component_int(QuadsCount)
zox_define_component_double(FPSDisplayTicker)
zox_system(FpsDisplaySystem, EcsOnUpdate, [none] FPSDisplay, [out] ZextData, [out] ZextDirty, [out] FPSDisplayTicker)
zox_system(QuadsLabelSystem, EcsOnUpdate, [none] QuadsCountLabel, [out] QuadsCount, [out] ZextDirty, [out] ZextData)
zoxel_end_module(GameUI)

#endif
