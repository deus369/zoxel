#ifndef zoxel_ui_game
#define zoxel_ui_game

// tags
//! A basic tag for a UI Element.
ECS_DECLARE(MainMenu);
ECS_DECLARE(FPSDisplay);
// components
// zoxel_component(PixelPosition, int2);
// util

// prefabs
#include "prefabs/main_menu.c"
// systems

//! Game UI Module, main menu, level select, etc.
/**
*   \todo FPSDisplay - display current fps at top right of ui. Uses text updating.
*/
void UIGameImport(ecs_world_t *world)
{
    ECS_MODULE(world, UIGame);
    ECS_TAG_DEFINE(world, MainMenu);
    // ECS_COMPONENT_DEFINE(world, PixelPosition);
    // Systems
    // zoxel_system(world, ElementRaycastSystem, EcsOnUpdate, [none] ElementRaycaster);
    // prefabs
    spawn_prefab_main_menu(world);
}
#endif