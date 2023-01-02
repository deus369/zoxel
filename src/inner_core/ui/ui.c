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
    zoxel_module(UI)
    zoxel_import_module(UICore)
    zoxel_import_module(Texts)
    zoxel_import_module(Elements)
    zoxel_import_module(UIGame)
}
#endif