#ifndef zoxel_game_ui
#define zoxel_game_ui

// settings
#include "settings/settings.c"
// zoxel_declare_components
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
// zoxel_include_functions
#include "fun/button_event_play_game.c"
#include "fun/button_event_pause_game.c"
#include "fun/button_event_exit_app.c"
#include "fun/button_event_return_to_game.c"
// zoxel_include_prefabs
#include "prefabs/menu_main.c"
#include "prefabs/menu_options.c"
#include "prefabs/menu_paused.c"
#include "prefabs/fps_display.c"
#include "prefabs/quad_count_label.c"
#include "prefabs/game_debug_label.c"
#include "prefabs/virtual_joystick_pointer.c"
#include "prefabs/virtual_joystick.c"
// zoxel_include_systems
#include "systems/fps_display_system.c"
#include "systems/quads_display_system.c"
#include "systems/game_debug_label_system.c"

void spawn_prefabs_game_ui(ecs_world_t *world) {
    spawn_prefab_main_menu(world);
    spawn_prefab_fps_display(world);
    spawn_prefab_pause_ui(world);
    spawn_prefab_options_ui(world);
    spawn_prefab_quad_count_label(world);
    spawn_prefab_game_debug_label(world);
    spawn_prefab_virtual_joystick_pointer(world);
    spawn_prefab_virtual_joystick(world);
}

zox_begin_module(GameUI)
// zoxel_define_components
zox_define_tag(MenuMain)
zox_define_tag(MenuOptions)
zox_define_tag(MenuPaused)
zox_define_tag(MenuInGame)
zox_define_tag(FPSDisplay)
zox_define_tag(QuadsCountLabel)
zox_define_tag(GameDebugLabel)
zox_define_tag(FrameDebuggerWindow)
zox_define_tag(JoystickUI)
zox_define_component_int(QuadsCount)
zox_define_component_double(FPSDisplayTicker)
// zoxel_define_systems
zox_system(FpsDisplaySystem, EcsOnUpdate, [none] FPSDisplay, [out] ZextData, [out] ZextDirty, [out] FPSDisplayTicker)
zox_system(QuadsLabelSystem, EcsOnUpdate, [none] QuadsCountLabel, [out] QuadsCount, [out] ZextDirty, [out] ZextData)
zox_system(GameDebugLabelSystem, EcsOnUpdate, [none] GameDebugLabel, [out] ZextDirty, [out] ZextData)
zoxel_end_module(GameUI)

#endif
