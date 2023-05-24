#ifndef zoxel_ui
#define zoxel_ui

#ifndef zoxel_on_android
    #define default_ui_scale 1.0f
#else
    #define default_ui_scale 2.0f
#endif
#include "core/ui_core.c"
#include "texts/texts.c"
#include "elements/elements.c"
#include "game/game_ui.c"
// #include "util/test_uis.c"
#include "fun/spawn_test_window.c"

zox_begin_module(UI)
zox_import_module(UICore)
zox_import_module(Texts)
zox_import_module(Elements)
zox_import_module(GameUI)
zoxel_end_module(UI)

#endif