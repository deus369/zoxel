#ifndef zoxel_ui
#define zoxel_ui

// settings
const float default_ui_scale = 1.0f;
const float android_ui_scale = 2.0f;
// sub modules
#include "core/ui_core.c"
#include "texts/texts.c"
#include "elements/elements.c"
#include "game/ui_game.c"
// util
#include "util/test_uis.c"

//! The UI contains submodules for ui.
void UIImport(ecs_world_t *world)
{
    zoxel_define_module(UI)
    ECS_IMPORT(world, UICore)
    ECS_IMPORT(world, Texts);
    ECS_IMPORT(world, Elements);
    ECS_IMPORT(world, UIGame);
}
#endif