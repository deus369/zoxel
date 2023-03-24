#ifndef zoxel_ui
#define zoxel_ui

const float default_ui_scale = 1.0f;
const float android_ui_scale = 2.0f;
#include "core/ui_core.c"
#include "texts/texts.c"
#include "elements/elements.c"
#include "game/ui_game.c"
#include "util/test_uis.c"

void UIImport(ecs_world_t *world) {
    zoxel_log("         > importing ui\n");
    zoxel_module(UI)
    zoxel_import_module(UICore)
    zoxel_import_module(Texts)
    zoxel_import_module(Elements)
    zoxel_import_module(UIGame)
    zoxel_log("         > imported ui\n");
}
#endif