#ifndef zoxel_ui_game
#define zoxel_ui_game

// tags
ECS_DECLARE(MainMenu);
ECS_DECLARE(OptionsUI);
ECS_DECLARE(PauseUI);
ECS_DECLARE(FPSDisplay);
// components
zoxel_component(FPSDisplayTicker, double);
// util
// prefabs
#include "prefabs/main_menu.c"
#include "prefabs/fps_display.c"
#include "prefabs/pause_ui.c"
#include "prefabs/options_ui.c"
// systems
#include "systems/fps_display_system.c"
#include "systems/play_game_button_system.c"
#include "systems/exit_game_button_system.c"

//! Game UI Module, main menu, level select, etc.
void UIGameImport(ecs_world_t *world)
{
    ECS_MODULE(world, UIGame);
    ECS_TAG_DEFINE(world, MainMenu);
    ECS_TAG_DEFINE(world, OptionsUI);
    ECS_TAG_DEFINE(world, PauseUI);
    ECS_TAG_DEFINE(world, FPSDisplay);
    ECS_COMPONENT_DEFINE(world, FPSDisplayTicker);
    // systems
    // fps display has to be single thread for now - zoxel_system
    zoxel_system_main_thread(world, FpsDisplaySystem, EcsOnUpdate,
        [out] FPSDisplayTicker, [out] ZextDirty, [out] ZextData);
    zoxel_button_system(PlayGameButtonSystem, elements.PlayGameButton)
    zoxel_button_system(ExitGameButtonSystem, elements.ExitGameButton)
    // prefabs
    spawn_prefab_main_menu(world);
    spawn_prefab_fps_display(world);
    spawn_prefab_pause_ui(world);
    spawn_prefab_options_ui(world);
}
#endif