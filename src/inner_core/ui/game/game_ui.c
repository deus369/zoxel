#ifndef zox_mod_game_ui
#define zox_mod_game_ui

#include "settings/settings.c"
zox_declare_tag(MenuMain)
zox_declare_tag(MenuOptions)
zox_declare_tag(MenuPaused)
zox_declare_tag(MenuGame)
zox_declare_tag(MenuGameTouch)
zox_declare_tag(FPSDisplay)
zox_declare_tag(QuadsCountLabel)
zox_declare_tag(GameDebugLabel)
zox_declare_tag(FrameDebuggerWindow)
zox_declare_tag(JoystickUI)
zox_declare_tag(Tooltip)
zox_declare_tag(Taskbar)
zox_component_int(QuadsCount)
zox_component_double(FPSDisplayTicker)
#include "util/menu_main.c"
#include "util/menu_options.c"
#include "util/menu_paused.c"
#include "util/game_loading.c"
#include "prefabs/prefabs.c"
#include "systems/fps_display_system.c"
#include "systems/quads_display_system.c"

zox_begin_module(GameUI)
zox_define_tag(MenuMain)
zox_define_tag(MenuOptions)
zox_define_tag(MenuPaused)
zox_define_tag(MenuGame)
zox_define_tag(MenuGameTouch)
zox_define_tag(FPSDisplay)
zox_define_tag(QuadsCountLabel)
zox_define_tag(GameDebugLabel)
zox_define_tag(FrameDebuggerWindow)
zox_define_tag(JoystickUI)
zox_define_tag(Tooltip)
zox_define_tag(Taskbar)
zox_define_component_int(QuadsCount)
zox_define_component_double(FPSDisplayTicker)
zox_system(FpsDisplaySystem, EcsOnUpdate, [none] FPSDisplay, [out] ZextData, [out] ZextDirty, [out] FPSDisplayTicker)
zox_system(QuadsLabelSystem, EcsOnUpdate, [none] QuadsCountLabel, [out] QuadsCount, [out] ZextDirty, [out] ZextData)
spawn_prefabs_game_ui(world);
zoxel_end_module(GameUI)

#endif
