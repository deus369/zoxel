#ifndef zoxel_game_ui
#define zoxel_game_ui

// settings
const color virtual_joystick_color = (color) { 44, 33, 33, 55 };
const color virtual_joystick_pointer_color = (color) { 88, 22, 22, 200 };
const int2 virtual_joystick_size = (int2) { 300, 300 }; // 240
const int2 virtual_joystick_pointer_size = (int2) { 120, 120 }; // 100
// zoxel_declare_components
zox_declare_tag(MainMenu)
zox_declare_tag(OptionsUI)
zox_declare_tag(PauseUI)
zox_declare_tag(FPSDisplay)
zox_declare_tag(QuadsCountLabel)
zox_declare_tag(GameDebugLabel)
zox_component(QuadsCount, int)
zox_component(FPSDisplayTicker, double)
// zoxel_include_functions
#include "fun/button_event_play_game.c"
#include "fun/button_event_exit_app.c"
#include "fun/button_event_return_to_game.c"
// zoxel_include_prefabs
#include "prefabs/main_menu.c"
#include "prefabs/fps_display.c"
#include "prefabs/pause_ui.c"
#include "prefabs/options_ui.c"
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
zox_define_tag(MainMenu)
zox_define_tag(OptionsUI)
zox_define_tag(PauseUI)
zox_define_tag(FPSDisplay)
zox_define_tag(QuadsCountLabel)
zox_define_tag(GameDebugLabel)
zox_define_component(QuadsCount)
zox_define_component(FPSDisplayTicker)
// zoxel_define_systems
zox_system(FpsDisplaySystem, EcsPostUpdate, [none] FPSDisplay, [out] ZextData, [out] ZextDirty, [out] FPSDisplayTicker)
zox_system(QuadsLabelSystem, EcsPostUpdate, [none] QuadsCountLabel, [out] QuadsCount, [out] ZextDirty, [out] ZextData)
zox_system(GameDebugLabelSystem, EcsPostUpdate, [none] GameDebugLabel, [out] ZextDirty, [out] ZextData)
zoxel_end_module(GameUI)

#endif
