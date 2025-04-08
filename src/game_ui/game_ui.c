// todo: find a way to add game modules onto game menu - add stats ui on etc
#ifndef zox_mod_game_ui
#define zox_mod_game_ui

// todo: use a byte index instead for menu type
#include "data/settings.c"
#include "data/taskbar.c"
#include "data/menus.c"
zox_component_byte(MenuType)    // index for menus
zox_declare_tag(MenuMain)
zox_declare_tag(MenuOptions)
zox_declare_tag(MenuPaused)
zox_declare_tag(MenuGame)
zox_declare_tag(MenuGameTouch)
zox_declare_tag(MenuStart)
zox_declare_tag(FPSDisplay)
zox_declare_tag(QuadsCountLabel)
zox_declare_tag(GameDebugLabel)
zox_declare_tag(FrameDebuggerWindow)
zox_declare_tag(JoystickUI)
zox_declare_tag(Taskbar)
zox_component_int(QuadsCount)
zox_component_double(FPSDisplayTicker)
#include "util/util.c"
#include "prefabs/prefabs.c"
#include "systems/fps_display_system.c"
#include "systems/quads_display_system.c"
#include "systems/device_mode_ui_system.c"

void dispose_gameui(ecs_world_t *world, void *ctx) {
    dispose_hook_taskbar();
}

zox_begin_module(GameUI)
    zox_module_dispose(dispose_gameui)
    initialize_hook_taskbar();
    zox_define_component_byte(MenuType)
    zox_define_tag(MenuMain)
    zox_define_tag(MenuOptions)
    zox_define_tag(MenuPaused)
    zox_define_tag(MenuGame)
    zox_define_tag(MenuGameTouch)
    zox_define_tag(MenuStart)
    zox_define_tag(FPSDisplay)
    zox_define_tag(QuadsCountLabel)
    zox_define_tag(GameDebugLabel)
    zox_define_tag(FrameDebuggerWindow)
    zox_define_tag(JoystickUI)
    zox_define_tag(Taskbar)
    zox_define_component_int(QuadsCount)
    zox_define_component_double(FPSDisplayTicker)
    zox_system_1(DeviceModeUISystem, EcsOnUpdate, [in] DeviceMode, [in] DeviceModeDirty, [in] GameLink, [in] CanvasLink) // note: must update before DeviceModeDirtySystem
    zox_system(FpsDisplaySystem, EcsOnUpdate, [none] FPSDisplay, [out] TextData, [out] ZextDirty, [out] FPSDisplayTicker)
    zox_system(QuadsLabelSystem, EcsOnUpdate, [none] QuadsCountLabel, [out] QuadsCount, [out] ZextDirty, [out] TextData)
    spawn_prefabs_game_ui(world);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_paused,
        .component_id = MenuPaused,
        .texture_name = "game_icon"
    });
zox_end_module(GameUI)

#endif
