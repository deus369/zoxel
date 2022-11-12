#ifndef zoxel_ui
#define zoxel_ui

// sub modules
#include "core/ui_core.c"
#include "texts/texts.c"
#include "game/ui_game.c"
// util
#include "util/test_uis.c"

//! The UI contains submodules for ui.
void UIImport(ecs_world_t *world)
{
    ECS_MODULE(world, UI);
    ECS_IMPORT(world, UICore)
    ECS_IMPORT(world, Texts);
    ECS_IMPORT(world, UIGame);
    #ifdef zoxel_test_uis
    spawn_test_uis(world);
    #endif
}
#endif